#pragma once

#include "Color.h"
#include "FrameBuffer.h"
#include "Object.h"
#include <cstdint> 

class Canvas {
public:
	using s_t = float;

	Canvas(int width, int height);
	void draw(s_t deltaTime);
	const FrameBuffer& getFrameBuffer() const;

private:
	int width;
	int height;
	FrameBuffer frameBuffer;
	std::vector<Object> objectsList;

	void init();
};
