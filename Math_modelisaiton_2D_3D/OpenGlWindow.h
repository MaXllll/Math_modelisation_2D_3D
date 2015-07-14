
#include <QtWidgets\qopenglwidget.h>
#include <QtGui\qevent.h>

class OpenGlWindow : public QOpenGLWidget
{


protected:
	void initializeGL();
	void paintGL();
	void mousePressEvent(QMouseEvent * event);
};

