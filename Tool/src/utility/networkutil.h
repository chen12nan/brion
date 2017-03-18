#ifndef NETWORKUTILITY_H
#define NETWORKUTILITY_H

#include <QString>

class NetworkUtil
{
public:
    NetworkUtil();

    /**
      获得公有ip
      */
    QString public_ip();

    /**
      通过公有ip定位城市
     */
    QString location(const QString& pub);


    QString getHtml(const QString& url);
    QString getNetIP(QString code);
    QString ip2city(const QString& ip);
    QString city();
};

#endif // NETWORKUTILITY_H
