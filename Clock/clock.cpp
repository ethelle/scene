#include <QtGui>
#include "clock.h"
#include <time.h>
Clock::Clock(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("Clock"));
    resize(200, 240);

    ClockWidget *clockWidget = new ClockWidget;

    QPushButton *buttonGMT = new QPushButton;
    buttonGMT->setText(tr("GMT"));
    QPushButton *buttonLocal = new QPushButton;
    buttonLocal->setText(tr("Local"));


    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(buttonGMT);
    layout->addWidget(buttonLocal);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(clockWidget,0,0);
    mainLayout->addLayout(layout,1,0);
    setLayout(mainLayout);

    connect(buttonGMT, SIGNAL(clicked()), clockWidget, SLOT(timeGMT()));
    connect(buttonLocal, SIGNAL(clicked()), clockWidget, SLOT(timeLoc()));
}

ClockWidget::ClockWidget(QWidget *parent)
     : QWidget(parent)
 {
     setBackgroundRole(QPalette::Midlight);
     setAutoFillBackground(true);

     locTime = 1;
 }

void ClockWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setWindow(-100,-100,200,200);
    int side = qMin(width(), height());
    painter.setViewport((width() - side) / 2, (height() - side) / 2,
                            side, side);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::darkCyan, 2, Qt::SolidLine, Qt::RoundCap));
    painter.setBrush(QBrush(Qt::lightGray, Qt::SolidPattern));
    painter.drawEllipse(-80,-80, 160, 160);

    // clock dial

    for (int i = 0; i <= 60; ++i) {
        if ((i % 5 == 0)&&(i!=0)) {
            painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap));
            painter.drawEllipse(-1.5, -60, 3, 3);
            painter.drawText(-16, -75, 32, 30,
                                  Qt::AlignHCenter | Qt::AlignTop,
                                  QString::number(i/5));
        } else {
            painter.setPen(QPen(Qt::darkCyan, 1, Qt::SolidLine, Qt::RoundCap));
            painter.drawEllipse(0, -60, 1, 1);
        }
            painter.rotate(6);
    }

    painter.rotate(-6);


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
         timer->start(1000);


    tm *tm1;
    time_t time1;
    time1 = time(NULL);

    //time calculation

    if (locTime==0)
        tm1 = gmtime(&time1);
    else
        tm1 = localtime(&time1);

    int hour1 = tm1->tm_hour;
    int min1 = tm1->tm_min;
    int sec1 = tm1->tm_sec;

    //hour hand

    painter.save();
    painter.rotate(30.0 * ((hour1 + min1 / 60.0)));//hour
    painter.fillRect(-3, -45, 6, 55, QBrush(Qt::black, Qt::SolidPattern));
    painter.restore();

    //minute hand

    painter.save();
    painter.rotate(6 * min1);
    painter.fillRect(-2, -60, 4, 70, QBrush(Qt::black, Qt::SolidPattern));//min
    painter.restore();

    //second hand

    painter.save();
    painter.rotate(6 * sec1);
    painter.fillRect(-1, -65, 2, 75, QBrush(Qt::red, Qt::SolidPattern));//sec
    painter.restore();

    painter.setBrush(QBrush(Qt::darkCyan, Qt::SolidPattern));
    painter.drawEllipse(-3, -3, 6, 6);

}


void ClockWidget::timeLoc()
{
    locTime = 1;
}

void ClockWidget::timeGMT()
{
    locTime = 0;
}
