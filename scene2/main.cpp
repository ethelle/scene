#include <QtGui>

#include "mainWindow.h"

using namespace scene;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	MainWindow mainWindow;
	mainWindow.show();

	return app.exec();
}
