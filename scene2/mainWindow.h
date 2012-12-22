#pragma once

#include <QtGui>
#include <QMainWindow>

#include "scene.h"

namespace scene {

	class MainWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		MainWindow();

	protected:

	private:
		MScene *mScene;
		QGraphicsView *mView;

	private slots:
		void addChair();
		void addTable();
		void removeObject();
		void clearScene();
	};

}
