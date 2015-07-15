#include "Widget.h"
#include <QtWidgets\qboxlayout.h>
#include <QtWidgets\qslider.h>
#include <QtCore\qdebug.h>
#include "OpenGlWindow.h"

OpenGlWindow* glWindow;

// Window dimensions
const GLuint WIDTH = 1200, HEIGHT = 800;

Widget::Widget()
{
	setMinimumSize(WIDTH, HEIGHT);
	model.degree = 4;
	model.pas = 100;

	QVBoxLayout* mainLayout;
	setLayout(mainLayout = new QVBoxLayout);
	
	QVBoxLayout* controlsayout;
	mainLayout->addLayout(controlsayout = new QVBoxLayout);
	mainLayout->addWidget(glWindow = new OpenGlWindow(&model));

	QHBoxLayout* lightPositionLayout;
	controlsayout->addLayout(lightPositionLayout = new QHBoxLayout);

	//QSlider* m_slider = new QSlider(Qt::Horizontal, this);

	lightPositionLayout->addWidget(dSlider = new customSlider(4, 1, 4, false, 10, "Degre"));
	lightPositionLayout->addWidget(pSlider = new customSlider(100, 10, 1000, false, 40, "Pas"));

	connect(pSlider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
	connect(dSlider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
}


void Widget::sliderValueChanged()
{
	model.degree = dSlider->value();
	model.pas = pSlider->value();
	glWindow->repaint();
}
