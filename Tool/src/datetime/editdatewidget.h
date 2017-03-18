#ifndef EDITDATEWIDGET_H
#define EDITDATEWIDGET_H

#include <QWidget>
#include <QLineEdit>

class EditDateWidget : public QWidget
{
    Q_OBJECT

public:
    enum Type{
        Year,
        Month,
        Day
    };

public:
    explicit EditDateWidget(Type type, QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);

signals:

public slots:
    void setText();

private:
    QLineEdit *m_lineEdit;
    QRect m_plus;
    QRect m_sub;
    QRect m_text;
    Type m_type;
    QString m_unit;
    QString m_dateText;
};

class TimeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TimeWidget(QWidget* parent = 0);

public slots:
    void setHourText();
    void setMinuteText();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);

private:
    QLineEdit *m_hourEdit;
    QLineEdit *m_minuteEdit;
    QRect m_hour;
    QRect m_minute;

    QString m_hourText;
    QString m_minuteText;

    QFont m_font;
};

#endif // EDITDATEWIDGET_H
