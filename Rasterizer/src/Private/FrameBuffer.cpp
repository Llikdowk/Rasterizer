#include "FrameBuffer.h"
#include <assert.h>
#include <algorithm>

FrameBuffer::~FrameBuffer() {
	delete[] framebuffer;
}

FrameBuffer::FrameBuffer(int width, int height)
		: width(width),
		  height(height),
		  framebuffer(new uint32_t[width * height]) {
	clear(0xFFFFFFff);
}

/*
FrameBuffer::FrameBuffer(FrameBuffer&& fb)
	: 
	width(fb.width), 
	height(fb.height),
	frameBuffer(fb.frameBuffer)
{
	fb.frameBuffer = nullptr;
}
*/


FrameBuffer::FrameBuffer(const FrameBuffer& fb)
		:
		width(fb.width),
		height(fb.height),
		framebuffer(new uint32_t[width * height]) {
	std::copy(fb.framebuffer, fb.framebuffer + fb.width * fb.height, this->framebuffer);
}


void FrameBuffer::setPixel(int x, int y, rgba8_t color) {
	assert(x >= 0 && x < width);
	assert(y >= 0 && y < height);
	framebuffer[y * width + x] = color;
}

auto FrameBuffer::getPixel(int x, int y) const -> const rgba8_t& {
	assert(x >= 0 && x < width);
	assert(y >= 0 && y < height);
	return framebuffer[y * width + x];
}

void FrameBuffer::clear(rgba8_t color) {
	std::fill(framebuffer, framebuffer + width * height, color);
	//frameBuffer.fill(color);
}

auto FrameBuffer::getFrameBuffer() const -> const rgba8_t* {
	return &framebuffer[0];
}
