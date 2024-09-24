#ifndef COLOR
#define COLOR

struct Color
{
	double r = 0;
	double g = 0;
	double b = 0;

	double a = 0;
};

const Color WHITE = Color{ 1.f,1.f,1.f,1.f };
const Color BLACK = Color{ 0.f,0.f,0.f,1.f };
const Color BLACK_TRANSPARENT = Color{ 0.f,0.f,0.f,0.8f };
const Color RED = Color{ 1.f,0.f,0.f,1.f };
const Color BOARD = Color{ 0.6f,0.f,0.f,1.f };
const Color GREEN = Color{ 0.f,1.f,0.f,1.f };
const Color BLUE = Color{ 0.f,0.f,1.f,1.f };
const Color CYAN = Color{ 0.f,0.5f,0.5f,1.f };
const Color YELLOW = Color{ 0.5f,0.5f,0.0f,1.f };
const Color GRAY = Color{ 0.5f,0.5f,0.5f,1 };
const Color GRAY_TRANSPARENT = Color{ 0.5f,0.5f,0.5f,0.6f };

void SetBackColor(Color color);
void SetForeColor(Color color);

#endif // !COLOR
