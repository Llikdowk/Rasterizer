#pragma once
#include "Color.h"
#include "Framebuffer.h"
#include <cstdint> 

class Canvas
{
public:
	Canvas(int width, int height);
	void draw();
	const Framebuffer& getFramebuffer() const;
private:
	void drawPixel(int x, int y, Color color);
	Framebuffer framebuffer;
};

