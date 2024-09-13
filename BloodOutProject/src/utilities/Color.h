#ifndef COLOR
#define COLOR

struct Color
{
	double r = 0;
	double g = 0;
	double b = 0;

	double a = 0;
};

const Color WHITE = Color{ 1,1,1,1 };
const Color BLACK = Color{ 0,0,0,1 };

#endif // !COLOR
