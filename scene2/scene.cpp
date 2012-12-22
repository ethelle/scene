#include <QtGui>

#include "scene.h"
#include "mainWindow.h"

using namespace scene;

MScene::MScene(QObject *parent)
	: QGraphicsScene(parent)
{
	mItem = NULL;
	mMouseDeltaPos.setX(0);
	mMouseDeltaPos.setY(0);
	mX1 = 0;
	mY1 = 0;
	mPenColor = Qt::black;
}

void MScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	if ((itemToAdd() == 1) || (itemToAdd() == 2)) {
		if (itemToAdd() == 1) {
			mWidth1 = 50;
			mHeight1 = 60;
			mBrushColor = Qt::blue;
		} else if (itemToAdd() == 2) {
			mWidth1 = 100;
			mHeight1 = 70;
			mBrushColor = Qt::red;
		}

		QGraphicsRectItem * currentItem = new QGraphicsRectItem(0, this);

		currentItem->setRect(QRectF(mX1, mY1, mWidth1, mHeight1));
		currentItem->setPos(mouseEvent->scenePos());
		currentItem->setPen(QPen(mPenColor));
		currentItem->setBrush(QBrush(mBrushColor));
		currentItem->setFlag(QGraphicsItem::ItemIsMovable, true);
		currentItem->setFlag(QGraphicsItem::ItemIsSelectable, true);

		if ((this->collidingItems(currentItem).isDetached())
			|| !(sceneRect().contains(mouseEvent->scenePos().x() + mWidth1
			, mouseEvent->scenePos().y() + mHeight1)))
		{
			this->removeItem(currentItem);
			delete currentItem;
		} else {
			this->addItem(currentItem);
			this->setItemToAdd(0);
		}

	} else {
		if (itemAt(mouseEvent->scenePos())) {
			mItem = static_cast<QGraphicsRectItem *>(itemAt(mouseEvent->scenePos()));
			mMouseDeltaPos = mItem->scenePos() - mouseEvent->scenePos();
		}
	}
	QGraphicsScene::mousePressEvent(mouseEvent);
}

void MScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	if (mItem) {
		QPointF const old = mItem->scenePos();
		mItem->setPos(mouseEvent->scenePos() + mMouseDeltaPos);

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
}

void MScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	mItem = NULL;
	mMouseDeltaPos.setX(0);
	mMouseDeltaPos.setY(0);
	QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void MScene::setItemToAdd(int i)
{
	mItemToAdd = i;
}

int MScene::itemToAdd() const
{
	return mItemToAdd;
}
