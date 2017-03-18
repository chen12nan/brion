#include "weatherwidget.h"
#include "weatheritem.h"
#include <QPainter>

WeatherWidget::WeatherWidget(QWidget *parent)
    :QWidget(parent),
      m_request(new WeatherRequest(this))
{
    setFixedSize(350, 530);

    m_iconsDict["thunderstorm with light rain"] = "://thunderstorm";
    m_iconsDict["thunderstorm with rain"] = "://thunderstorm";
    m_iconsDict["thunderstorm with heavy rain"] = "://heavy thunderstorm";
    m_iconsDict["light thunderstorm"] = "://thunderstorm";
    m_iconsDict["thunderstorm"] = "://thunderstorm";
    m_iconsDict["heavy thunderstorm"] = "://heavy thunderstorm";
    m_iconsDict["ragged thunderstorm"] = "://thunderstorm";
    m_iconsDict["thunderstorm with light drizzle"] ="://thunderstorm";
    m_iconsDict["thunderstorm with drizzle"] = "://thunderstorm";
    m_iconsDict["thunderstorm with heavy drizzle"] = "://thunderstorm";

    m_iconsDict["light intensity drizzle"] = "://drizzle";
    m_iconsDict["drizzle"] = "://drizzle";
    m_iconsDict["heavy intensity drizzle"] = "://moderate rain";
    m_iconsDict["light intensity drizzle rain"] = "://drizzle";
    m_iconsDict["drizzle rain"] = "://drizzle";
    m_iconsDict["heavy intensity drizzle rain"] = "://moderate rain";
    m_iconsDict["shower rain and drizzle"] = "://shower rain";
    m_iconsDict["heavy shower rain and drizzle"] = "://shower rain";
    m_iconsDict["shower drizzle"] = "://shower rain";

    m_iconsDict["light rain"] = "://drizzle";
    m_iconsDict["moderate rain"] = "://moderate rain";
    m_iconsDict["heavy intensity rain"] = "://heavy intensity rain";
    m_iconsDict["very heavy rain"] = "://very heavy rain";
    m_iconsDict["extreme rain"] = "://extreme rain";
    m_iconsDict["freezing rain"] = "://freezing rain";
    m_iconsDict["light intensity shower rain"] = "://shower rain";
    m_iconsDict["shower rain"] = "://shower rain";
    m_iconsDict["heavy intensity shower rain"] = "://shower rain";
    m_iconsDict["ragged shower rain"] = "://shower rain";

    m_iconsDict["light snow"] = "://light snow";
    m_iconsDict["snow"] = "://snow";
    m_iconsDict["heavy snow"] = "://heavy snow";
    m_iconsDict["sleet"] = "://sleet";
    m_iconsDict["shower sleet"] = "://sleet";
    m_iconsDict["light rain and snow"] = "://sleet";
    m_iconsDict["rain and snow"] = "://sleet";
    m_iconsDict["light shower snow"] = "://shower snow";
    m_iconsDict["shower snow"] = "://shower snow";
    m_iconsDict["heavy shower snow"] = "://shower snow";

    m_iconsDict["clear sky"] = "://clear sky";
    m_iconsDict["few clouds"] = "://few clouds";
    m_iconsDict["scattered clouds"] = "://few clouds";
    m_iconsDict["broken clouds"] = "://few clouds";
    m_iconsDict["overcast clouds"] = "://overcast clouds";

    m_iconsDict["tornado"] = "://tornado";
    m_iconsDict["tropical storm"] = "://tropical storm";
    m_iconsDict["hurricane"] = "://hurricane";
    m_iconsDict["cold"] = "://cold";
    m_iconsDict["hot"] = "://hot";
    m_iconsDict["windy"] = "://windy";
    m_iconsDict["hail"] = "://hail";
    m_iconsDict["fresh breeze"] = "://gale";
    m_iconsDict["strong breeze"] = "://gale";
    m_iconsDict["high wind, near gale"] = "://gale";
    m_iconsDict["gale"] = "://gale";
    m_iconsDict["severe gale"] = "://gale";
    m_iconsDict["storm"] = "://storm";
    m_iconsDict["violent storm"] = "://violent storm";

    connect(m_request, SIGNAL(refreshData(QList<WeatherItem>&)),
            this, SLOT(refreshView(QList<WeatherItem>&)));
}

void WeatherWidget::paintEvent(QPaintEvent *event)
{
    int count = m_request->count();
    if(count == 0)
        return;

    int h = (height() - 20)/count;
    int fh = h + 20;
    int y = 0;

    QPainter painter(this);
    QColor col = QColor(qrand()%255, qrand()%255, qrand()%255, 100);
    QPen pen1(Qt::white);
    painter.setPen(pen1);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(col);
    painter.drawRect(rect());
    for(int i= 0; i<count; i++)
    {
        QRect rect(0,y,width(),((i == 0) ? fh : h));
        QPoint center = rect.center();
//        painter.drawRect(rect);
        WeatherItem item = m_request->dayAt(i);

        QPixmap icon = QPixmap(this->icon(item));
        QRect iconRect(0,0,icon.width(), icon.height());
        iconRect.moveCenter(QPoint(center.x()/3, center.y()));
        painter.drawPixmap(iconRect, icon);

        QString text;
        if(i == 0)
        {
            painter.save();
            painter.setRenderHint(QPainter::Antialiasing);
            QFont font = painter.font();
            font.setPixelSize(20);
            QPen pen(Qt::white);
            painter.setPen(pen);
            painter.setFont(font);

            text = QString("%1°C").arg(int(item.day()+0.5));
            QRect textRect(iconRect.right()+10,rect.y(),50, rect.height());
            painter.drawText(textRect,Qt::AlignLeft|Qt::AlignVCenter, text);
            font.setPixelSize(10);
            painter.setFont(font);
            textRect.moveLeft(textRect.right());
            textRect.moveTop(textRect.top()+2);
            painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, item.description());

            QRect cityArea(rect.width() - 50 - iconRect.left()-20,rect.y(),90, rect.height()/2+6);
            QRect statusArea(rect.width() - 50 - iconRect.left()-10,cityArea.bottom(),70, rect.height()/2 -6);
            font.setPixelSize(16);
            painter.setFont(font);
            painter.drawText(cityArea, Qt::AlignBottom | Qt::AlignHCenter, m_request->city());
            font.setPixelSize(10);
            painter.setFont(font);
            painter.drawText(statusArea, Qt::AlignTop|Qt::AlignHCenter, QString("刚刚更新"));
            painter.restore();
        }
        else
        {
            painter.save();
            painter.setRenderHint(QPainter::Antialiasing);
            text = QString("%1-%2°C").arg((int)(item.min()+0.5)).arg((int)(item.max()+0.5));
            QRect textRect(iconRect.right()+10,rect.y(),100, rect.height());
            painter.drawText(textRect,Qt::AlignLeft|Qt::AlignVCenter, text);

            QRect weekArea(rect.width() - 50 - iconRect.left(),rect.y(),50, rect.height());
            painter.drawText(weekArea, Qt::AlignCenter, item.dayOfWeek());
            painter.restore();
        }
        y+=rect.height();
    }
}

void WeatherWidget::mousePressEvent(QMouseEvent *event)
{
    update();
}

QString WeatherWidget::icon(const WeatherItem &item)
{
    QStringList nights;
    nights<<"clear sky"<<"overcast clouds"<<"shower snow"
         <<"shower rain";
    if(nights.contains(item.description()))
    {
        QTime time = QTime::currentTime();
        if(time.hour() >= 18 || time.hour() <= 6)
        {
            return m_iconsDict[item.description()]+" night";
        }
        else
        {
            return m_iconsDict[item.description()];
        }
    }
    else
    {
        return m_iconsDict[item.description()];
    }
}

void WeatherWidget::refreshView(QList<WeatherItem> &items)
{
    update();
    show();
}
