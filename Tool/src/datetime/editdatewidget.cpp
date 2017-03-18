#include "editdatewidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QWheelEvent>
#include <QDate>
#include <QIntValidator>

EditDateWidget::EditDateWidget(Type type, QWidget *parent)
    : QWidget(parent),
      m_type(type)
{
    setFixedSize(QSize(387,35));
    m_lineEdit = new QLineEdit(this);

    if(m_type == Year)
    {
        m_unit = QString("年");
        m_dateText = QString().setNum(QDate::currentDate().year());
    }
    else if(m_type == Month)
    {
        m_unit = QString("月");
        m_dateText = QString().setNum(QDate::currentDate().month());
    }
    else
    {
        m_unit = QString("日");
        m_dateText = QString().setNum(QDate::currentDate().day());
    }

    m_lineEdit->setAlignment(Qt::AlignCenter);
    m_lineEdit->setText(m_dateText);
    m_lineEdit->setStyleSheet("QLineEdit{border:0px}");
    m_lineEdit->setStyleSheet("QLineEdit{background-color: transparent; border: 0px}");
    m_lineEdit->hide();
    connect(m_lineEdit, SIGNAL(returnPressed()),this,SLOT(setText()));
}

void EditDateWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRect rect = this->rect();
    painter.setPen(Qt::black);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect vplus = QRect(rect.width()-rect.height()*0.5-20 ,rect.height()*0.2,1,rect.height()*0.6);
    QRect hplus = QRect(0,0,vplus.height(),1);
    hplus.moveCenter(vplus.center());
    m_plus = QRect(hplus.left(),vplus.top(),hplus.width(), hplus.width());

    painter.drawRect(vplus);
    painter.drawRect(hplus);

    QRect vsub = hplus;
    vsub.moveLeft(rect.height()*0.2 + 20);
    painter.drawRect(vsub);
    m_sub = QRect(vsub.left(), vplus.top(), vsub.width(), vsub.width());


    QRect text = QRect(0,0,30,rect.height());
    text.moveCenter(rect.center());
    if(m_lineEdit->isHidden())
    {
        painter.drawText(text, Qt::AlignCenter, m_dateText);
    }
    m_text = text;

    QRect date = QRect(text.right(), text.top(), 20, text.height());
    painter.drawText(date, Qt::AlignCenter,m_unit);

}

void EditDateWidget::mousePressEvent(QMouseEvent *e)
{
    if(m_text.contains(e->pos()))
    {
        m_lineEdit->setGeometry(m_text.adjusted(-2,5,2,-5));
        m_lineEdit->show();
        m_lineEdit->setFocus();
    }
    else
    {
        m_lineEdit->hide();
    }

    if(m_plus.contains(e->pos()))
    {
        int date = m_dateText.toInt();
        ++date;
        m_dateText.setNum(date);
        m_lineEdit->setText(m_dateText);
    }

    if(m_sub.contains(e->pos()))
    {
        int date = m_dateText.toInt();
        --date;
        m_dateText.setNum(date);
        m_lineEdit->setText(m_dateText);
    }
    update();
}

void EditDateWidget::wheelEvent(QWheelEvent *e)
{
    if(m_lineEdit->isVisible())
    {
        QPoint angle = e->angleDelta();
        int date = m_dateText.toInt();

        if(angle.y() == -120)
        {
            ++date;
        }
        else
        {
            --date;
        }
        m_dateText.setNum(date);
        m_lineEdit->setText(m_dateText);
    }
}

void EditDateWidget::setText()
{
    m_dateText = m_lineEdit->text();
    m_lineEdit->hide();
    update();
}


TimeWidget::TimeWidget(QWidget *parent)
    :QWidget(parent)
{
    setFixedSize(180, 60);
    m_font.setPixelSize(32);

    QTime time = QTime::currentTime();
    m_hourText = QString("%1").arg(time.hour());
    m_minuteText = QString("%1").arg(time.minute());

    m_hour = QRect(0,0,75,height());
    m_minute = QRect(width()-75, 0, 75, height());

    m_hourEdit = new QLineEdit(this);
    m_hourEdit->setFont(m_font);
    m_hourEdit->setGeometry(m_hour);
    m_hourEdit->setStyleSheet("QLineEdit{background-color: transparent; border: 0px}");
    m_hourEdit->setAlignment(Qt::AlignCenter);
    m_hourEdit->setText(m_hourText);
    m_hourEdit->setValidator(new QIntValidator(0,23,this));
    m_hourEdit->hide();

    m_minuteEdit = new QLineEdit(this);
    m_minuteEdit->setFont(m_font);
    m_minuteEdit->setGeometry(m_minute);
    m_minuteEdit->setStyleSheet("QLineEdit{background-color: transparent; border: 0px}");
    m_minuteEdit->setAlignment(Qt::AlignCenter);
    m_minuteEdit->setText(m_minuteText);
    m_minuteEdit->setValidator(new QIntValidator(0,59,this));
    m_minuteEdit->hide();

    connect(m_hourEdit, SIGNAL(returnPressed()), this, SLOT(setHourText()));
    connect(m_minuteEdit, SIGNAL(returnPressed()), this, SLOT(setMinuteText()));
}

void TimeWidget::setHourText()
{
    m_hourText = m_hourEdit->text();
    m_hourEdit->hide();

    update();
}

void TimeWidget::setMinuteText()
{
    m_minuteText = m_minuteEdit->text();
    m_minuteEdit->hide();

    update();
}

void TimeWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(Qt::white);

    painter.fillRect(m_hour, QColor(100,100,100,20));
    painter.fillRect(m_minute, QColor(100,100,100,20));

    painter.setFont(m_font);

    if(!m_hourEdit->isVisible())
    {
        painter.drawText(m_hour, Qt::AlignCenter, m_hourText);
    }

    painter.drawText(QRect(m_hour.right(), 0, m_minute.left() - m_hour.right(), height()), Qt::AlignCenter, tr(":"));

    if(!m_minuteEdit->isVisible())
    {
        painter.drawText(m_minute, Qt::AlignCenter, m_minuteText);
    }
}

void TimeWidget::mousePressEvent(QMouseEvent *e)
{
    if(m_hourEdit->isHidden() && m_hour.contains(e->pos()))
    {
        m_hourEdit->setVisible(true);
        m_hourEdit->setFocus();
    }
    else
    {
        m_hourEdit->hide();
    }

    if(m_minuteEdit->isHidden() && m_minute.contains(e->pos()))
    {
        m_minuteEdit->setVisible(true);
        m_minuteEdit->setFocus();
    }
    else
    {
        m_minuteEdit->hide();
    }
}

void TimeWidget::wheelEvent(QWheelEvent *e)
{
    if(m_hourEdit->isVisible())
    {
        QPoint angle = e->angleDelta();
        int hour = m_hourText.toInt();
        if(angle.y() == -120)
        {
            ++hour;
        }
        else
        {
            --hour;
        }
        hour = (hour > 23) ? 0 : hour;
        hour = (hour < 0 ) ? 23 : hour;

        m_hourText.setNum(hour);
        m_hourEdit->setText(m_hourText);
    }


    if(m_minuteEdit->isVisible())
    {
        QPoint angle = e->angleDelta();
        int minute = m_minuteText.toInt();
        if(angle.y() == -120)
        {
            ++minute;
        }
        else
        {
            --minute;
        }
        minute = (minute > 59) ? 0 : minute;
        minute = (minute < 0 ) ? 59 : minute;

        m_minuteText.setNum(minute);
        m_minuteEdit->setText(m_minuteText);
    }
}


