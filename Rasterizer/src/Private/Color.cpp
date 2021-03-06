#include "Color.h"


Color operator*(const Color& color, float k) { // TODO: change this
	return Color::ColorNormalized(k * color.r / 255.0f, k * color.g / 255.0f, k * color.b / 255.0f, color.a / 255.0f);
}

Color operator*(float k, const Color& color) {
	return color * k;
}

Color Color::operator+(const Color& color) const {
	return Color((uint8_t) (r + color.r), g + color.g, b + color.b, a + color.a);
}

bool Color::operator==(const Color& color) const {
	return r == color.r && g == color.g && b == color.b && a == color.a;
}

bool Color::operator!=(const Color& color) const {
	return !(*this == color);
}

Color Color::decode(uint32_t color) {
	uint8_t r = (color & 0xFF000000) >> 6 * 4;
	uint8_t g = (color & 0x00FF0000) >> 4 * 4;
	uint8_t b = (color & 0x0000FF00) >> 2 * 4;
	uint8_t a = (color & 0x000000FF) >> 0 * 4;

	return Color(r, g, b, a);
}

uint32_t Color::encode(const Color& c) {
	uint32_t color = (c.r << 6 * 4) + (c.g << 4 * 4) + (c.b << 2 * 4) + (c.a << 0 * 4);
	return color;
}

const Color Color::Black = Color::ColorNormalized(0, 0, 0);
const Color Color::White = Color::ColorNormalized(1, 1, 1);
const Color Color::Red = Color::ColorNormalized(1, 0, 0);
const Color Color::Green = Color::ColorNormalized(0, 1, 0);
const Color Color::Blue = Color::ColorNormalized(0, 0, 1);
const Color Color::Magenta = Color::ColorNormalized(1, 0, 1);
const Color Color::Cyan = Color::ColorNormalized(0, 1, 1);
const Color Color::Yellow = Color::ColorNormalized(1, 1, 0);

