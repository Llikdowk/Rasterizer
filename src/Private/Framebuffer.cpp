#include "Framebuffer.h"
#include "Config.h"
#include <assert.h>
#include <algorithm>

Framebuffer::Framebuffer(int width, int height)
	: width(width), height(height), framebuffer(new rgba8_t[width*height])
{
	clear(0xFFFFFFff);
}

Framebuffer::Framebuffer(Framebuffer&& fb) 
	: 
	width(fb.width), 
	height(fb.height),
	framebuffer(fb.framebuffer)
{
	fb.framebuffer = nullptr;
}

Framebuffer::Framebuffer(const Framebuffer& fb)
	:
	width(fb.width),
	height(fb.height)
{
	std::copy(fb.framebuffer, fb.framebuffer + width*height, framebuffer);
}

Framebuffer::~Framebuffer()
{
	delete[] framebuffer;
}

void Framebuffer::setPixel(int x, int y, rgba8_t color)
{
	assert(x >= 0 && x < width);
	assert(y >= 0 && y < height);
	framebuffer[y*width + x] = color;
}

auto Framebuffer::getPixel(int x, int y) const -> const rgba8_t&
{
	assert(x >= 0 && x < width);
	assert(y >= 0 && y < height);
	return framebuffer[y*width + x];
}

void Framebuffer::clear(rgba8_t color)
{
	std::fill(framebuffer, framebuffer + width*height, color);
}

auto Framebuffer::getFramebuffer() const -> const rgba8_t*
{
	return framebuffer;
}
