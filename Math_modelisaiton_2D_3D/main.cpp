//Qt
#include <QtWidgets\qapplication.h>
#include <QtWidgets\qmainwindow.h>	
#include <QtWidgets\qmenubar.h>
#include <QtWidgets\qmenu.h>

//Custom
#include "OpenGlWindow.h"
#include "Widget.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);


	QMainWindow *window = new QMainWindow();
	window->setWindowTitle(QString::fromUtf8("QMenuBar Add Menu"));

	Widget widget;
	//widget.show();

	QAction* newBSplineA = new QAction(window);

	connect(newBSplineA, SIGNAL())

	QMenuBar *menu = new QMenuBar();

	QMenu* menu1 = new QMenu("New");
	QMenu* newBSplineMenu = new QMenu("New B-spline");
	menu1->addMenu(newBSplineMenu);

	QMenu* menu2 = new QMenu("Mode");
	menu2->addMenu(new QMenu("B-spline"));
	menu2->addMenu(new QMenu("Extrusion"));
	menu2->addMenu(new QMenu("Surface"));

	menu->addMenu(menu1);
	menu->addMenu(menu2);
	

	menu->setMinimumWidth(600);

	window->setCentralWidget(&widget);
	window->setMenuBar(menu);

	//OpenGlWindow window;
	//window.show();

	window->show();

	return app.exec();
}