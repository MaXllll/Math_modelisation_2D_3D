#include "math_modelisation_2d_3d_qt.h"
#include <qboxlayout.h>
#include "Widget.h"
#include <qdebug.h>

Widget* mainWidget;
Model model;

Math_modelisation_2D_3D_QT::Math_modelisation_2D_3D_QT(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	QHBoxLayout* layout = new QHBoxLayout;

	layout->addWidget(mainWidget = new Widget(&model));
	centralWidget()->setLayout(layout);

	createActions();
	createMenus();

	//readSettings();
}

void Math_modelisation_2D_3D_QT::newBSpline()
{
	mainWidget->newbSpline();
}

void Math_modelisation_2D_3D_QT::createPointMode()
{
	model.mode = model.CREATEPOINT;
	mainWidget->repaint();
}

void Math_modelisation_2D_3D_QT::movePointMode()
{
	model.mode = model.MOVEPOINT;
	mainWidget->repaint();
}

void Math_modelisation_2D_3D_QT::repeatPointMode()
{
	model.mode = model.REPEATPOINT;
	mainWidget->repaint();
}


void Math_modelisation_2D_3D_QT::createActions()
{
	//New Menu
	newAct = new QAction(tr("&New B-spline"), this);
	newAct->setShortcuts(QKeySequence::New);
	newAct->setStatusTip(tr("Create a B Spline"));
	connect(newAct, SIGNAL(triggered()), this, SLOT(newBSpline()));

	//Edit Menu
	createPointAct = new QAction(tr("&Create Point"), this);
	//createPointAct->setShortcuts(QKeySequence::New);
	createPointAct->setStatusTip(tr("Create new Point mode"));
	connect(createPointAct, SIGNAL(triggered()), this, SLOT(createPointMode()));

	movePointAct = new QAction(tr("&Move Point"), this);
	//movePointAct->setShortcuts(QKeySequence::New);
	movePointAct->setStatusTip(tr("Move a point mode"));
	connect(movePointAct, SIGNAL(triggered()), this, SLOT(movePointMode()));

	repeatPointAct = new QAction(tr("&Repeat Point"), this);
	//repeatPointAct->setShortcuts(QKeySequence::New);
	repeatPointAct->setStatusTip(tr("Repeat a point mode"));
	connect(repeatPointAct, SIGNAL(triggered()), this, SLOT(repeatPointMode()));
}

void Math_modelisation_2D_3D_QT::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAct);

	editMenu = menuBar()->addMenu(tr("&Edit"));
	editModeMenu = editMenu->addMenu(tr("&Mode"));
	editModeMenu->addAction(createPointAct);
	editModeMenu->addAction(movePointAct);
	editModeMenu->addAction(repeatPointAct);

	menuBar()->addSeparator();

	helpMenu = menuBar()->addMenu(tr("&Help"));
}

Math_modelisation_2D_3D_QT::~Math_modelisation_2D_3D_QT()
{

}

