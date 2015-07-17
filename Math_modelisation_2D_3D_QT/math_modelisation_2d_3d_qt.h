#ifndef MATH_MODELISATION_2D_3D_QT_H
#define MATH_MODELISATION_2D_3D_QT_H

#include <QtWidgets/QMainWindow>
#include "ui_math_modelisation_2d_3d_qt.h"

class Math_modelisation_2D_3D_QT : public QMainWindow
{
	Q_OBJECT

public:
	Math_modelisation_2D_3D_QT(QWidget *parent = 0);
	~Math_modelisation_2D_3D_QT();

private slots:
	void newFile();

private:
	void createActions();
	void createMenus();
	//QString strippedName(const QString &fullFileName);

	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *helpMenu;
	QToolBar *fileToolBar;
	QToolBar *editToolBar;
	QAction *newAct;
	QAction *openAct;
	QAction *saveAct;
	QAction *saveAsAct;
	QAction *exitAct;
	QAction *cutAct;
	QAction *copyAct;
	QAction *pasteAct;
	QAction *aboutAct;
	QAction *aboutQtAct;

private:
	Ui::Math_modelisation_2D_3D_QTClass ui;

};

#endif // MATH_MODELISATION_2D_3D_QT_H
