#pragma once

struct Model
{
	enum Mode
	{
		CREATEPOINT,
		MOVEPOINT,
		REPEATPOINT
	};

	float degree;
	float pas;
	Mode mode;
};