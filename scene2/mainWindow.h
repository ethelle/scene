#pragma once

#include <QtGui>
#include <QMainWindow>

#include "scene.h"
class MWindow : public QMainWindow
{
    Q_OBJECT

public:
   MWindow();

public slots:
   void addChair();
   void addTable();
   void remObject();
   void clearScene();

protected:

private:
    MScene *scene;
    QGraphicsView *view;
};

