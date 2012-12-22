#include <QtGui>

#include "mainWindow.h"
#include "scene.h"

using namespace scene;

MainWindow::MainWindow()
{
	mScene = new MScene(this);
	mScene->setSceneRect(0, 0, 500, 500);
	mView = new QGraphicsView(mScene);

	QPushButton *chairButton = new QPushButton("Add chair");
	QPushButton *tableButton = new QPushButton("Add table");
	QPushButton *removeButton = new QPushButton("Remove");
	QPushButton *clearButton = new QPushButton("Clear all");

	QObject::connect(chairButton, SIGNAL(clicked()), this, SLOT(addChair()));
	QObject::connect(tableButton, SIGNAL(clicked()), this, SLOT(addTable()));
	QObject::connect(removeButton, SIGNAL(clicked()), this, SLOT(removeObject()));
	QObject::connect(clearButton, SIGNAL(clicked()), this, SLOT(clearScene()));

	mView->setRenderHint(QPainter::Antialiasing, true);
	mView->setCacheMode(QGraphicsView::CacheBackground);
	mView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	mView->setFixedSize(502, 502);

	//Layout setup

	QVBoxLayout *vLayout1 = new QVBoxLayout;
	QVBoxLayout *vLayout2 = new QVBoxLayout;
	QHBoxLayout *hLayout1 = new QHBoxLayout;
	vLayout1->addWidget(mView);
	vLayout2->addWidget(chairButton);
	vLayout2->addWidget(tableButton);
	vLayout2->addWidget(removeButton);
	vLayout2->addWidget(clearButton);
	vLayout2->addStretch();
	hLayout1->addLayout(vLayout1);
	hLayout1->addLayout(vLayout2);

	QWidget *widget = new QWidget;
	widget->setLayout(hLayout1);
	setCentralWidget(widget);
}

void MainWindow::addChair()
{
	mScene->setItemToAdd(1);
}

void MainWindow::addTable()
{
	mScene->setItemToAdd(2);
}

void MainWindow::removeObject()
{
	foreach (QGraphicsItem *item, mScene->selectedItems()) {
		mScene->removeItem(item);
		delete item;
	}
}

void MainWindow::clearScene()
{
	foreach (QGraphicsItem *item, mScene->items()) {
		mScene->removeItem(item);
		delete item;
	}
}
