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
const Color RED = Color{ 1,0,0,1 };
const Color GREEN = Color{ 0,1,0,1 };
const Color BLUE = Color{ 0,0,1,1 };
const Color YELLOW = Color{ 0,0.5,0.5,1 };
const Color GRAY = Color{ 0.5,0.5,0.5,1 };
const Color GRAY_TRANSPARENT = Color{ 0.5,0.5,0.5,0.4 };

void SetBackColor(Color color);
void SetForeColor(Color color);

#endif // !COLOR
