#include "Canvas.h"



Canvas::Canvas()
{
}


Canvas::~Canvas()
{
}

void Canvas::draw()
{
	for (int i = 0; i < 480; ++i) // DISPLAY_WIDTH = 480 <- should not be hardcoded but transferred
	{
		drawPixel(i, 15, Color::White * 0.75f);
	}
	drawPixel(15, 25, Color::Black);
}

void Canvas::drawPixel(int x, int y, Color color)
{
	fb.set(x, y, color.getCoded());
}
