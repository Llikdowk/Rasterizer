#pragma once
#include "Color.h"
#include "Framebuffer.h"

class Canvas
{
public:
	Canvas();
	~Canvas();
	void draw();
private:
	void drawPixel(int x, int y, Color color);
	Framebuffer fb;
};

