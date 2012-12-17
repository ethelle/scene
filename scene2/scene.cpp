#include <QtGui>

#include "scene.h"
#include "mainWindow.h"

MScene::MScene(QObject *parent)
    : QGraphicsScene(parent)
{
    mItem = NULL;
    mdMouse.setX(0);
    mdMouse.setY(0);
}

void MScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if ((getmAddItem() == 1) || (getmAddItem() == 2)) {
        if (getmAddItem() == 1) {
            x1 = 0;
            y1 = 0;
            w1 = 50;
            h1 = 60;
            mPenColor = Qt::black;
            mBrushColor = Qt::blue;
        } else if (getmAddItem() == 2) {
            x1 = 0; y1 = 0; w1 = 100; h1 = 70; mPenColor = Qt::black;
            mBrushColor = Qt::red;
        }

        QGraphicsRectItem * mItem2 = new QGraphicsRectItem(0, this);

        mItem2->setRect(QRectF(x1, y1, w1, h1));
        mItem2->setPos(mouseEvent->scenePos());
        mItem2->setPen(QPen(mPenColor));
        mItem2->setBrush(QBrush(mBrushColor));
        mItem2->setFlag(QGraphicsItem::ItemIsMovable, true);
        mItem2->setFlag(QGraphicsItem::ItemIsSelectable, true);

        if ((this->collidingItems(mItem2).isDetached())
                || (sceneRect().contains(mouseEvent->scenePos().x() + w1
                                         , mouseEvent->scenePos().y() + h1))==false)
        {
            this->removeItem(mItem2);
            delete mItem2;
        } else {
            this->addItem(mItem2);
            this->setmAddItem(0);
        }
      //  this->setmAddItem(0);

    } else {
        if (itemAt(mouseEvent->scenePos())) {
            mItem = (QGraphicsRectItem *) itemAt(mouseEvent->scenePos());
            mdMouse = mItem->scenePos() - mouseEvent->scenePos();
        }
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void MScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mItem) {
        QPointF old = mItem->scenePos();
        QPointF oldm = mouseEvent->scenePos();
        mItem->setPos(mouseEvent->scenePos() + mdMouse);

        if ((this->collidingItems(mItem).isDetached())
             || !(sceneRect().contains(
                     mItem->scenePos().x() + mItem->rect().width(),
                     mItem->scenePos().y() + mItem->rect().height()))
             || !(sceneRect().contains(
                     mItem->scenePos().x() ,
                     mItem->scenePos().y() )))
        {
            mItem->setPos(old);
        }
    }

  //  QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void MScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    mItem = NULL;
    mdMouse.setX(0);
    mdMouse.setY(0);
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void MScene::setmAddItem(int i)
{
    mAddItem = i;
}

int MScene::getmAddItem()
{
    return mAddItem;
}
