#pragma once

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsSceneMoveEvent>

class QGraphicsSceneMouseEvent;
class QPointF;
class QGraphicsRectItem;

class MScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MScene(QObject *parent = 0);
    void setmAddItem(int i);
    int getmAddItem();

protected:
    int mAddItem;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    int x1;
    int y1;
    int h1;
    int w1;
    QColor mPenColor;
    QColor mBrushColor;
    QGraphicsRectItem *mItem;
    QPointF mdMouse;

};

