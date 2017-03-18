#ifndef DATETIME_H
#define DATETIME_H

#include "datetime_global.h"
#include <QPointF>

class DATETIMESHARED_EXPORT Datetime
{

public:
    Datetime();

    QPointF transform(double lon, double lat);
    QPointF mercator(double lon, double lat);
};

#endif // DATETIME_H
