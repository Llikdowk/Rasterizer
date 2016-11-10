#pragma once
#include <cstdint>
#include "Utils.h"

struct Color
{
public:
	const uint8_t r, g, b, a;

	Color(float r, float g, float b, float a) :
		r(utils::clamp(r, 0.0f, 1.0f)*255.0f), 
		g(utils::clamp(g, 0.0f, 1.0f)*255.0f), 
		b(utils::clamp(b, 0.0f, 1.0f)*255.0f), 
		a(utils::clamp(a, 0.0f, 1.0f)*255.0f) {}

	Color(float r, float g, float b) : Color(r, g, b, 1.0f) {}
	Color() : Color(0.0f, 0.0f, 0.0f, 1.0f) {};
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : // TODO: should this be public?
		r(r), g(g), b(b), a(a)
	{}

	static uint32_t encode(const Color&);
	static Color decode(uint32_t);

	static const Color Black;
	static const Color White;
	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Magenta;
	static const Color Cyan;
	static const Color Yellow;
};

Color operator*(const Color&, float);
Color operator*(float, const Color&);
Color operator+(const Color&, const Color&);
