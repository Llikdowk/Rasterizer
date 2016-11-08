#include "Canvas.h"
#include "Config.h"


Canvas::Canvas(int width, int height) : framebuffer(Framebuffer(width, height))
{
}

void Canvas::draw()
{
	framebuffer.clear(Color::Black.getCoded());
	for (int i = 0; i < Config::windowWidth; ++i)
	{
		drawPixel(i, 15, Color::Cyan);
	}
	drawPixel(15, 25, Color::Magenta);
}

void Canvas::drawPixel(int x, int y, Color color)
{
	framebuffer.setPixel(x, y, color.getCoded());
}

const Framebuffer& Canvas::getFramebuffer() const
{
	return framebuffer;
}