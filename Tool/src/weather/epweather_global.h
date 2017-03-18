#ifndef EPWEATHER_GLOBAL_H
#define EPWEATHER_GLOBAL_H


#include <QtCore/qglobal.h>

#if defined(DATABASE_LIBRARY)
#  define WEATHER_EXPORT Q_DECL_EXPORT
#else
#  define WEATHER_EXPORT Q_DECL_IMPORT
#endif

#endif // EPWEATHER_GLOBAL_H
