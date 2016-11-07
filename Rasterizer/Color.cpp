#include "Color.h"

Color operator*(const Color& color, float k)
{
	return Color((float)color.r/255.0f*k, (float)color.g/255.0f*k, (float)color.b/255.0f*k, color.a/255.0f);
}

Color operator*(float k, const Color& color)
{
	return color * k;
}

uint32_t Color::getCoded()
{
	uint32_t color = 16*16*16*16*16*16*r + 16*16*16*16*g + 16*16*b + a; // assuming big endian, change mult by << operator
	return color;
}

const Color Color::Black = Color();
const Color Color::White = Color(1, 1, 1);
const Color Color::Red = Color(1, 0, 0);
const Color Color::Green = Color(0, 1, 0);
const Color Color::Blue = Color(0, 0, 1);
const Color Color::Magenta = Color(1, 0, 1);
const Color Color::Cyan = Color(0, 1, 1);
const Color Color::Yellow = Color(1, 1, 0);