#include <QtWidgets\qopenglwidget.h>
#include <QtGui\qevent.h>
#include "Model.h"

class OpenGlWindow : public QOpenGLWidget
{

public:
	OpenGlWindow(Model* model);
	Model* model;

protected:
	void initializeGL();
	void paintGL();
	void mousePressEvent(QMouseEvent * event);

private:
	void knot(int n, int c, int x[]);
	void basis(int c, float t, int npts, int x[], float n[]);
	void bspline(int npts, int k, int p1);
	void calculateBSpline();


};

