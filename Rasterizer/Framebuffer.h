#pragma once
#include <cstdint> 

class Framebuffer
{
public:
	using rgba8_t = uint32_t;

	const int width;
	const int height;

	Framebuffer(int width, int height);
	~Framebuffer();
	
	Framebuffer(const Framebuffer&);
	Framebuffer(Framebuffer&&);
	Framebuffer operator=(const Framebuffer&) = delete;
	Framebuffer operator=(Framebuffer&&) = delete;

	void setPixel(int x, int y, rgba8_t color);
	const rgba8_t& getPixel(int x, int y) const;
	const rgba8_t* getFramebuffer() const;
	void clear(rgba8_t color);

private:
	rgba8_t* framebuffer;
};

