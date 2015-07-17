#include "math_modelisation_2d_3d_qt.h"
#include <qboxlayout.h>
#include "Widget.h"
#include <qdebug.h>

Widget* mainWidget;

Math_modelisation_2D_3D_QT::Math_modelisation_2D_3D_QT(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	QHBoxLayout* layout = new QHBoxLayout;

	layout->addWidget(mainWidget = new Widget);
	centralWidget()->setLayout(layout);

	createActions();
	createMenus();

	//readSettings();
}

void Math_modelisation_2D_3D_QT::newFile()
{
	mainWidget->newbSpline();
}

void Math_modelisation_2D_3D_QT::createActions()
{
	newAct = new QAction(tr("&New B-spline"), this);
	newAct->setShortcuts(QKeySequence::New);
	newAct->setStatusTip(tr("Create a B Spline"));
	connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));
}

void Math_modelisation_2D_3D_QT::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAct);

	editMenu = menuBar()->addMenu(tr("&Edit"));

	menuBar()->addSeparator();

	helpMenu = menuBar()->addMenu(tr("&Help"));
}

Math_modelisation_2D_3D_QT::~Math_modelisation_2D_3D_QT()
{

}

