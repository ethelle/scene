#pragma once

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsSceneMoveEvent>

class QGraphicsSceneMouseEvent;
class QPointF;
class QGraphicsRectItem;

namespace scene {
	class MScene : public QGraphicsScene
	{
		Q_OBJECT

	public:
		MScene(QObject *parent = 0);
		void setItemToAdd(int i);
		int itemToAdd() const;

	protected:
		void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
		void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
		void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

	private:
		int mItemToAdd;
		int mX1;
		int mY1;
		int mHeight1;
		int mWidth1;
		QColor mPenColor;
		QColor mBrushColor;
		QGraphicsRectItem *mItem;
		QPointF mMouseDeltaPos;
	};
}
