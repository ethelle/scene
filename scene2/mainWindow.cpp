#include <QtGui>

#include "mainWindow.h"
#include "scene.h"

MWindow::MWindow()
{
    scene = new MScene(this);
    scene->setSceneRect(0, 0, 500, 500);
    view = new QGraphicsView(scene);

    QPushButton *mButChair = new QPushButton("Add chair");
    QPushButton *mButTable = new QPushButton("Add table");
    QPushButton *mButRem = new QPushButton("Remove");
    QPushButton *mButClear = new QPushButton("Clear all");

    QObject::connect(mButChair, SIGNAL(clicked()), this, SLOT(addChair()));
    QObject::connect(mButTable, SIGNAL(clicked()), this, SLOT(addTable()));
    QObject::connect(mButRem, SIGNAL(clicked()), this, SLOT(remObject()));
    QObject::connect(mButClear, SIGNAL(clicked()), this, SLOT(clearScene()));

    view->setRenderHint(QPainter::Antialiasing, true);
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setFixedSize(502, 502);

    //Layout setup

    QVBoxLayout *pvbxLayout1 = new QVBoxLayout;
    QVBoxLayout *pvbxLayout2 = new QVBoxLayout;
    QHBoxLayout *pvbxLayout3 = new QHBoxLayout;
    pvbxLayout1->addWidget(view);
    pvbxLayout2->addWidget(mButChair);
    pvbxLayout2->addWidget(mButTable);
    pvbxLayout2->addWidget(mButRem);
    pvbxLayout2->addWidget(mButClear);
    pvbxLayout2->addStretch();
    pvbxLayout3->addLayout(pvbxLayout1);
    pvbxLayout3->addLayout(pvbxLayout2);

    QWidget *widget = new QWidget;
    widget->setLayout(pvbxLayout3);
    setCentralWidget(widget);

}

void MWindow::addChair()
{
    scene->setmAddItem(1);
}

void MWindow::addTable()
{
    scene->setmAddItem(2);
}

void MWindow::remObject()
{
    foreach (QGraphicsItem *item, scene->selectedItems()) {
    scene->removeItem(item);
    delete item;
    }
}

void MWindow::clearScene()
{
    foreach (QGraphicsItem *item, scene->items()) {
    scene->removeItem(item);
    delete item;
    }
}


