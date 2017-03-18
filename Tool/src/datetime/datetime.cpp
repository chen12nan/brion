#include "datetime.h"
#include <cmath>
#include <QPixmap>
#include <QDebug>
#include <QPainter>

const double PI=3.1415926;

Datetime::Datetime()
{
    QPixmap pixmap = QPixmap("/home/xingkd/Desktop/world.png", "PNG");
    qDebug()<<Q_FUNC_INFO<<pixmap.size();
    double lon = 110.341667, lat = 29.106819;
    mercator(lon, lat);
    QPointF pos = transform(lon, lat);
    qDebug()<<Q_FUNC_INFO<<pos;

    double ratex = pos.x()*72/(2.54*1030);
    double ratey = pos.y()*72/(2.54*400);

    double lon1 = 121.458061, lat1=31.222219;
    QPointF pos1 = transform(lon1, lat1);

    qDebug()<<pos1.x()*72/(2.54*ratex);
    qDebug()<<pos1.y()*72/(2.54*ratey);
}

QPointF Datetime::transform(double lon, double lat)
{
    double L = 6381372 * PI * 2;     // 地球周长
    double W = L;     // 平面展开后，x轴等于周长
    double H = L / 2;     // y轴约等于周长一半
    double mill = 2.3;      // 米勒投影中的一个常数，范围大约在正负2.3之间
    double x = lon * PI / 180;     // 将经度从度数转换为弧度
    double y = lat * PI / 180;     // 将纬度从度数转换为弧度

    // 这里是米勒投影的转换
    y = 1.25 * log( tan( 0.25 * PI + 0.4 * y ) );
    // 这里将弧度转为实际距离
    x = ( W / 2 ) + ( W / (2 * PI) ) * x;
    y = ( H / 2 ) - ( H / ( 2 * mill ) ) * y;
    // 转换结果的单位是公里
    // 可以根据此结果，算出在某个尺寸的画布上，各个点的坐标

    qDebug()<<Q_FUNC_INFO<<log(10);
    return QPointF(x,y);
}

QPointF Datetime::mercator(double lon, double lat)
{
    QPointF mer;
    double x = lon*(20037508.34)/180;
    double y = log(tan(90+lat)*PI/360)/(PI/180);

    y = y*20037508.34/180;
    mer.setX(x);
    mer.setY(y);
    qDebug()<<mer;
    return mer;
}
