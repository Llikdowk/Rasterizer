//
// Created by Llikdowk on 27-Nov-16.
//

#pragma once

#include <iostream>
#include "Vector.h"
#include "Color.h"
#include "FrameBuffer.h"

class MeshRenderer {
public:
	MeshRenderer(FrameBuffer& fb) : frameBuffer(fb) {}
	virtual ~MeshRenderer() = default;// { std::cout << "meshRenderer destructor" << std::endl; }

	virtual void drawPixel(float x, float y, Color color) const = 0;
	virtual void drawPixel(int x, int y, Color color) const = 0;
	virtual void drawLine(float xA, float yA, float xB, float yB, Color colorA, Color colorB) const = 0;
	virtual void drawLine(lmath::Vector2 v, lmath::Vector2 w, Color color) const = 0;

protected:
	FrameBuffer& frameBuffer;
};


class NaiveRenderer : public MeshRenderer {
public:
	NaiveRenderer(FrameBuffer& fb) : MeshRenderer(fb) {}

	virtual void drawPixel(float x, float y, Color color) const override;
	virtual void drawPixel(int x, int y, Color color) const override;
	virtual void drawLine(float xA, float yA, float xB, float yB, Color colorA, Color colorB) const override;
	virtual void drawLine(lmath::Vector2 v, lmath::Vector2 w, Color color) const override;
};