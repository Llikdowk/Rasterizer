#include "Canvas.h"
#include "Mesh.h"

#include <Matrix4.h>
#include <Vector.h>

#include <assert.h>
#include <math.h>
#include <iostream>
#include <Transform.h>
#include <Object.h>


Canvas::Canvas(int width, int height)
	: 
	width(width), 
	height(height),
	framebuffer(FrameBuffer(width, height))
{
	framebuffer.clear(Color::encode(Color::Black));

}

void Canvas::draw(s_t deltaTime) {
	static s_t elapsedTime = deltaTime;
	elapsedTime += deltaTime;

	framebuffer.clear(Color::encode(Color::Black));
	/*
	float s = std::sin(-elapsedTime) * 0.5f + 0.5f;
	float c = std::cos(elapsedTime) * 0.5f + 0.5f;
	drawLine(0.5f, 0.5f, c, s,
		utils::lerp(Color::Magenta, Color::Yellow, s),
		utils::lerp(Color::Cyan, Color::Red, s)
	);
	 */
	using namespace lmath;

	//Matrix4 worldToCamera = Matrix4::identity;
	Transform camera; // TODO: transform into object
	camera.translate(0, 0, -2);
	//translation
	//worldToCamera[2][3] = -2.0f;
	float d = 1.0f;
	Matrix4 projection = Matrix4::identity;
	projection[3][3] = 0;
	projection[3][2] = d;

	Object cube;
	cube.mesh = Mesh::cube;
	cube.transform.rotate_y(elapsedTime);
	cube.transform.scale(sinf(elapsedTime), sinf(elapsedTime), sinf(elapsedTime));


	for (int i = 0; i < 8; ++i) { // over vertices
		Vector4 worldPoint = cube.transform.matrix * cube.mesh.vertices[i];
		worldPoint.w = 1.0f;
		Vector4 cameraPoint = camera.inverse * worldPoint; // camera-> world to camera, not local to world
		Vector4 screenPoint = projection * cameraPoint;
		screenPoint.x /= screenPoint.w;
		screenPoint.y /= screenPoint.w;
		screenPoint.z /= screenPoint.w;
		//NDC
		screenPoint.x = (screenPoint.x + 1.0f) / 2.0f;
		screenPoint.y = (screenPoint.y + 1.0f) / 2.0f;
		drawPixel(screenPoint.x, screenPoint.y, Color::White);
	}

}



void Canvas::drawPixel(float x, float y, Color color)
{
	//assert(x >= 0.0f && x <= 1.0f);
	//assert(y >= 0.0f && y <= 1.0f);
	if (x >= 0.0f && x <= 1.0f && y >= 0.0f && y <= 1.0f) {
		drawPixel(static_cast<int>(x * (width - 1)), static_cast<int>(y * (height - 1)), color);
	}
}

void Canvas::drawPixel(int x, int y, Color color)
{
	framebuffer.setPixel(x, y, Color::encode(color));
}

void Canvas::drawLine(float xA, float yA, float xB, float yB, Color colorA, Color colorB)
{
	float xStep = std::abs((xB - xA) / width);
	float yStep = std::abs((yB - yA) / height);
	float step = std::max(xStep, yStep);
	step *= 1.0/std::sqrt((xB-xA)*(xB-xA) + (yB-yA)*(yB-yA)) ;

	for (float t = 0.0f; t <= 1.0f; t += step)
	{
		Color c = utils::lerp(colorA, colorB, t);
		float x = utils::lerp(xA, xB, t);
		float y = utils::lerp(yA, yB, t);
		drawPixel(x, y, c);
	}
}

const FrameBuffer& Canvas::getFramebuffer() const
{
	return framebuffer;
}