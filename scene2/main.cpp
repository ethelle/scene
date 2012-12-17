#include <QtGui>

#include "mainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MWindow mwindow;
    mwindow.show();

    return app.exec();
}
