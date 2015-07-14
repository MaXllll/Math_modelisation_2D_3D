#include "Widget.h"
#include <QtWidgets\qboxlayout.h>
#include "OpenGlWindow.h"

// Window dimensions
const GLuint WIDTH = 1200, HEIGHT = 800;

Widget::Widget()
{
	setMinimumSize(WIDTH, HEIGHT);

	QVBoxLayout* mainLayout;
	setLayout(mainLayout = new QVBoxLayout);
	
	QVBoxLayout* controlsayout;
	mainLayout->addLayout(controlsayout = new QVBoxLayout);
	mainLayout->addWidget(new OpenGlWindow);
}


Widget::~Widget()
{
}
