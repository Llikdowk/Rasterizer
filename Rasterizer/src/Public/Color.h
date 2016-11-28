#pragma once
#include <cstdint>
#include "Utils.h"

struct Color
{
private:
	uint8_t data[4];

public:
	const uint8_t& r = data[0];
	const uint8_t& g = data[1];
	const uint8_t& b = data[2];
	const uint8_t& a = data[3];

	Color(const Color& c) {
		data[0] = c.r;
		data[1] = c.g;
		data[2] = c.b;
		data[3] = c.a;
	}
	Color& operator=(const Color& c) {
		data[0] = c.r;
		data[1] = c.g;
		data[2] = c.b;
		data[3] = c.a;
		return *this;
	}

	static Color ColorNormalized(float r, float g, float b, float a = 1.0f) {
		return Color(r, g, b, a);
	}

	static Color Color256(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
		return Color(r, g, b, a);
	}

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

private:

    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	{
		data[0] = r;
		data[1] = g;
		data[2] = b;
		data[3] = a;
	}

	Color(float r, float g, float b, float a) {
		data[0] = (utils::clamp(r, 0.0f, 1.0f)*255.0f);
		data[1] = (utils::clamp(g, 0.0f, 1.0f)*255.0f);
		data[2] = (utils::clamp(b, 0.0f, 1.0f)*255.0f);
		data[3] = (utils::clamp(a, 0.0f, 1.0f)*255.0f);
	}

public:
    Color operator+ (const Color&) const;
	bool operator== (const Color&) const;
	bool operator!=(const Color&) const;
	//friend std::ostream& operator<<(std::ostream&, const Color&);
};

Color operator*(const Color&, float);
Color operator*(float, const Color&);

