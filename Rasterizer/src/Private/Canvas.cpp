#include "Canvas.h"
#include "Mesh.h"

#include <Matrix4.h>
#include <Vector.h>

#include <assert.h>
#include <math.h>
#include <iostream>
#include <Transform.h>


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
	Transform camera;
	camera.translate(0, 0, -2);
	//translation
	//worldToCamera[2][3] = -2.0f;
	Matrix4 projection = Matrix4::identity;
	Transform cube_transform;
	cube_transform.rotate_y(elapsedTime);
	cube_transform.scale(sinf(elapsedTime), sinf(elapsedTime), sinf(elapsedTime));
	/*
	Matrix4 rotation = {
			cosf(elapsedTime), 0, sinf(elapsedTime), 0,
			0, 1, 0, 0,
			-sinf(elapsedTime), 0, cosf(elapsedTime), 0,
			0, 0, 0, 1
	};
	 */

	Mesh cube;

	for (int i = 0; i < 8; ++i) { // over vertices
		Vector4 worldPoint = cube_transform.inverse * cube.vertices[i];
		worldPoint.w = 1.0f;
		Vector4 cameraPoint = camera.inverse * worldPoint; // camera-> world to camera, not local to world
		projection[0][0] = 1.0f/-cameraPoint.z;
		projection[1][1] = 1.0f/-cameraPoint.z;
		projection[2][2] = 1.0f/-cameraPoint.z;
		Vector4 screenPoint = projection * cameraPoint;
		//NDC
		screenPoint.x = (screenPoint.x + 1.0f) / 2.0f;
		screenPoint.y = (screenPoint.y + 1.0f) / 2.0f;
		drawPixel(screenPoint.x, screenPoint.y, Color::White);
	}

}



void Canvas::drawPixel(float x, float y, Color color)
{
	assert(x >= 0.0f && x <= 1.0f);
	assert(y >= 0.0f && y <= 1.0f);
	drawPixel(static_cast<int>(x*(width-1)), static_cast<int>(y*(height-1)), color);
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