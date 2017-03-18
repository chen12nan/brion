#include "networkutil.h"
#include <QProcess>
#include <QDebug>
#include <QHostAddress>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include "GeoIP.h"
#include "GeoIPCity.h"

// sudo apt-get install geoip-database-extra
// sudo apt-get install geoip-bin (geoiplookup geoiplookup6)

// sudo apt-get install libgeoip-dev
// https://github.com/maxmind/geoip-api-c.git


#ifdef   __cplusplus
extern "C" {
#endif

    GEOIP_API unsigned long _GeoIP_lookupaddress(const char *host);

#ifdef   __cplusplus
 }
#endif
static const char * _mk_NA( const char * p )
{
    return p ? p : "N/A";
}


NetworkUtil::NetworkUtil()
{

}

QString NetworkUtil::public_ip()
{
    QProcess ip;
    ip.start("curl", QStringList() << "ip.cn");
    if (!ip.waitForStarted())
        return false;
    ip.closeWriteChannel();

    if (!ip.waitForFinished())
        return false;

    QString result = ip.readAll();
    result = result.fromUtf8(result.toStdString().c_str());
    QStringList split = result.split(" ");
    foreach(QString str, split)
    {
        if(str.contains("IP：") && str.length() > 8)
            return str.split("：").at(1);
    }
    return QString();
}

QString NetworkUtil::location(const QString &pub)
{
    if(pub.isNull())
        return QString();
    QHostAddress addr(pub);

    QString program;
    if(addr.protocol() == QAbstractSocket::IPv4Protocol)
    {
        program = QString("geoiplookup");
    }
    else if(addr.protocol() == QAbstractSocket::IPv6Protocol)
    {
        program = QString("geoiplookup6");
    }
    else
    {
        return QString();
    }

    QProcess location;
    location.start(program, QStringList() << pub);
    if (!location.waitForStarted())
        return false;
    location.closeWriteChannel();

    if (!location.waitForFinished())
        return false;

    QString result = location.readAll();
    QStringList list = result.split(":");
    if(list.count() > 1)
    {
        result = list[1];
        QStringList details = result.split(",");
        if(details.count() > 6)
        {
            QString city = QString("%1:%2:%3").arg(details.at(0).simplified())
                    .arg(details.at(2).simplified()).arg(details.at(3).simplified());
            return city;
        }
    }
    return QString();
}

QString NetworkUtil::getHtml(const QString &url)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    QByteArray responseData;
    QEventLoop eventLoop;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    responseData = reply->readAll();
    reply->deleteLater();
    manager->deleteLater();
    return QString(responseData);
}

QString NetworkUtil::getNetIP(QString code)
{
    if(code.isEmpty())
    {
        qDebug()<<"network invalid";
        return QString("0.0.0.0");
    }

    QString web = code.replace(" ", "");
    web = web.replace("\r", "");
    web = web.replace("\n", "");
    QStringList list = web.split("<br/>");
    if(list.size() < 4)
        return "0.0.0.0";
    QString tar = list[3];
    QStringList ip = tar.split("=");
    return (ip.count() > 1) ? ip[1] : QString("0.0.0.0");
}

QString NetworkUtil::ip2city(const QString &ip)
{
   GeoIP * gi = GeoIP_open_type(GEOIP_CITY_EDITION_REV1, GEOIP_STANDARD | GEOIP_SILENCE);
   uint32_t ipnum = _GeoIP_lookupaddress(ip.toStdString().c_str());
   GeoIPRecord *gir = GeoIP_record_by_ipnum(gi, ipnum);

   if (NULL == gir) {
       qDebug()<<"IP Address not found, return the last city";
       // 暂时返回wuhan， 应该返回最后一次使用的城市
       return QString("wuhan");
   }else {
       /*
       QString str = QString("%1: %2, %3, %4, %5, %6, %7, %8, %9, %10").arg(GeoIPDBDescription[GEOIP_CITY_EDITION_REV1])
               .arg(gir->country_code).arg(_mk_NA(gir->region))
               .arg(_mk_NA(GeoIP_region_name_by_code(gir->country_code,gir->region)))
               .arg(_mk_NA(gir->city)).arg(_mk_NA(gir->postal_code))
               .arg(gir->latitude).arg(gir->longitude).arg(gir->metro_code)
               .arg(gir->area_code);
               */

       return (gir->city ? QString(gir->city) : QString());
   }
}

QString NetworkUtil::city()
{
    QString ip = getNetIP(getHtml("http://whois.pconline.com.cn/"));
    QString city = ip2city(ip);
    return city.isEmpty() ? QString("wuhan") : city;
}

