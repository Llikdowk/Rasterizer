#include "Canvas.h"
#include <assert.h>
#include <math.h>

Canvas::Canvas(int width, int height)
	: 
	width(width), 
	height(height),
	framebuffer(Framebuffer(width, height))
{}

void Canvas::draw(float deltaTime)
{
	framebuffer.clear(Color::encode(Color::Black));
	for (int i = 0; i < width; ++i)
	{
		drawPixel(i, 15, Color::Cyan);
		drawPixel(i, 25, Color::Magenta);
		for (int j = 0; j < height; ++j)
		{
			if (i == j)
			{
				drawPixel(i, j, Color::Green);
			}
		}
	}

	float factor = std::min(width, height);
	float resolution = 1.0f;
	float step = 1.0f / (resolution * factor);
	for (float x = 0.0f, y = 0.0f; x <= 1.0f && y <= 1.0f; x += step, y += step)
	{
		drawPixel(x, y, Color::White);
	}

	static float t = deltaTime; // elapsed time - todo: get all time variables easily
	t += deltaTime;
	float s = std::sin(t/100.0f) * 0.5f + 1.0f;
	float c = std::cos(t/100.0f) * 0.5f + 1.0f;
	drawLine(0.0f, 0.5f, 0.75f, s*0.5f, s * Color::Magenta, c * Color::Cyan); // fixme: problem with hack min/max to create line
}



void Canvas::drawPixel(float x, float y, Color color)
{
	assert(x >= 0.0f && x <= 1.0f);
	assert(y >= 0.0f && y <= 1.0f);
	drawPixel(static_cast<int>(x*width), static_cast<int>(y*height), color);
}

void Canvas::drawPixel(int x, int y, Color color)
{
	framebuffer.setPixel(x, y, Color::encode(color));
}

void Canvas::drawLine(float xA, float yA, float xB, float yB, Color colorA, Color colorB)
{
	float s = std::max(height, width);
	float xStep = (xB - xA) / s;
	float yStep = (yB - yA) / s;
	float colorStep = std::max(xStep, yStep);

	float xMin = std::min(xA, xB);
	float xMax = std::max(xA, xB);
	float yMin = std::min(yA, yB);
	float yMax = std::max(yA, yB);

	float x = xMin;
	float y = yMin;
	float t = 0.0f;
	while (x <= xMax && y <= yMax)
	{
		Color c = Utils::lerp(colorA, colorB, t);
		drawPixel(x, y, c);
		x += xStep;
		y += yStep;
		t += colorStep;
	}
}

const Framebuffer& Canvas::getFramebuffer() const
{
	return framebuffer;
}