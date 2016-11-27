//
// Created by Llikdowk on 27-Nov-16.
//

#pragma once

#include "Vector.h"
#include "Color.h"
#include "FrameBuffer.h"

class RenderMesh {
public:
	RenderMesh(FrameBuffer* fb)
			: frameBuffer(fb) {}
	virtual ~RenderMesh() {} // TODO read about this (virtual destructor)

	virtual void drawPixel(float x, float y, Color color) const = 0;
	virtual void drawPixel(int x, int y, Color color) const = 0;
	virtual void drawLine(float xA, float yA, float xB, float yB, Color colorA, Color colorB) const = 0;
	virtual void drawLine(lmath::Vector2 v, lmath::Vector2 w, Color color) const = 0;

protected:
	FrameBuffer* const frameBuffer;
};


class NaiveRender : public RenderMesh {
public:
	NaiveRender(FrameBuffer* fb) : RenderMesh(fb) {}
	virtual ~NaiveRender() {} // TODO read about this (virtual destructor)

	virtual void drawPixel(float x, float y, Color color) const override;
	virtual void drawPixel(int x, int y, Color color) const override;
	virtual void drawLine(float xA, float yA, float xB, float yB, Color colorA, Color colorB) const override;
	virtual void drawLine(lmath::Vector2 v, lmath::Vector2 w, Color color) const override;
};