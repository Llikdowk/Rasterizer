#pragma once
#include "Color.h"
#include "Framebuffer.h"
#include <cstdint> 

class Canvas
{
public:
	Canvas(int width, int height);
	void draw(float deltaTime);
	const Framebuffer& getFramebuffer() const;

private:
	Framebuffer framebuffer;
	int width;
	int height;

	void drawPixel(int x, int y, Color color);
	void drawPixel(float x, float y, Color color); // normalized screen coordinates: [0, 1]
	
	void drawLine(float xA, float yA, float xB, float yB, Color colorA, Color colorB);
};