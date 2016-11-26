#pragma once
#include "Color.h"
#include "FrameBuffer.h"
#include "Object.h"
#include <cstdint> 

class Canvas
{
public:
	using s_t = float;

	Canvas(int width, int height);
	void draw(s_t deltaTime);
	const FrameBuffer& getFramebuffer() const;

private:
	int width;
	int height;
	FrameBuffer framebuffer;

	std::vector<Object> objectsList;
	void init();

	void drawPixel(int x, int y, Color color);
	void drawPixel(float x, float y, Color color); // normalized screen coordinates: [0, 1]
	void drawLine(float xA, float yA, float xB, float yB, Color colorA, Color colorB);
	void drawLine(Vector2 v, Vector2 w, Color color);
};