#include <QtWidgets\qopenglwidget.h>
#include <QtGui\qevent.h>
#include "Model.h"
#include "Point.h"

class OpenGlWindow : public QOpenGLWidget
{

public:
	OpenGlWindow(Model* model);
	Model* model;
	void newBSpline();

protected:
	void initializeGL();
	void paintGL();
	void mousePressEvent(QMouseEvent * event);
	void mouseMoveEvent(QMouseEvent *event);


private:
	//BSpline
	void knot(int n, int c, int x[]);
	void basis(int c, float t, int npts, int x[], float n[]);
	void bspline(int npts, int k, int p1, int current);
	void calculateBSpline(int i);
	void initializeBSpline();
	void paintBSpline();

	//B Surface
	Point Decasteljau(float t, std::vector<Point> points);
	std::vector<Point> CalculateBezier(std::vector<Point> polygon);
	void initializeGrid();
	void paintBSurface();

	//Utils
	Point* searchClosedPoint(Point click);



	Point* movingPoint;
	bool hasClick = false;

};

