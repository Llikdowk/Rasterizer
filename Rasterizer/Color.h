#pragma once
#include <cstdint>
#include "Utils.h"

struct Color
{
public:
	const uint8_t r, g, b, a;

	Color::Color(float r, float g, float b, float a) : 
		r(Utils::clamp(r, 0.0f, 1.0f)*255.0f), 
		g(Utils::clamp(g, 0.0f, 1.0f)*255.0f), 
		b(Utils::clamp(b, 0.0f, 1.0f)*255.0f), 
		a(Utils::clamp(a, 0.0f, 1.0f)*255.0f) {}

	Color(float r, float g, float b) : Color(r, g, b, 1.0f) {}
	Color() : Color(0.0f, 0.0f, 0.0f, 1.0f) {};

	uint32_t getCoded();

	static const Color Black;
	static const Color White;
	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Magenta;
	static const Color Cyan;
	static const Color Yellow;
};

Color operator*(const Color& color, float k);
Color operator*(float k, const Color& color);

