#pragma once
#include <cstdint> 

class Framebuffer
{
public:
	using color_t = uint32_t;

	Framebuffer();
	~Framebuffer();
	void set(int x, int y, color_t c);
	color_t get(int x, int y);
	void clear(color_t c);

private:
	color_t frameBuffer[];
};

