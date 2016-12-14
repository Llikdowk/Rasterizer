#pragma once
#include <cstdint>
#include <vector>

class FrameBuffer
{
public:
	using rgba8_t = uint32_t;

	const int width;
	const int height;

	~FrameBuffer();
	FrameBuffer(int width, int height);

	FrameBuffer(const FrameBuffer&);// = delete;
	FrameBuffer(FrameBuffer&&) = delete;
	FrameBuffer operator=(const FrameBuffer&) = delete;
	FrameBuffer operator=(FrameBuffer&&) = delete;

	void setPixel(int x, int y, rgba8_t color);
	const rgba8_t& getPixel(int x, int y) const;
	const rgba8_t* getFrameBuffer() const;
	void clear(rgba8_t color);

private:
	//std::vector<rgba8_t> framebuffer; //should be fixed!
	rgba8_t* framebuffer;
};

