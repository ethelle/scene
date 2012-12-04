#ifndef CALC_H
#define CALC_H

#include <QWidget>

class QPushButton;

class Clock : public QWidget
{
    Q_OBJECT

public:
    Clock(QWidget *parent = 0);

private:
    QPushButton *buttonGMT;
    QPushButton *buttonLocal;

};

class ClockWidget : public QWidget
{
    Q_OBJECT

public:
    ClockWidget(QWidget *parent = 0);
    int locTime;

public slots:
    void timeLoc();
    void timeGMT();

protected:
    void paintEvent(QPaintEvent *event);

};
#endif // CALC_H
