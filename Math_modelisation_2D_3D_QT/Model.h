#pragma once

struct Model
{
	enum SplineMode
	{
		CREATEPOINT,
		MOVEPOINT,
		REPEATPOINT
	};

	enum Mode
	{
		BSPLINE,
		EXTRUSION,
		BSURFACE
	};



	float degree;
	float pas;
	SplineMode splineMode;
	Mode mode;
};