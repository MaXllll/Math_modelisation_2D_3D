#include "customSlider.h"
#include <QtWidgets\qwidget.h>
#include "Model.h"


class Widget : public QWidget
{
	Q_OBJECT

	customSlider* dSlider;
	customSlider* pSlider;

	Model model;

private slots:
	void sliderValueChanged();

//signals:
//	void valueChanged(float newValue);

public:
	Widget();
	void newbSpline();
};

