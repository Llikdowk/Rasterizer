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
	init();
}

void Canvas::init() {
	framebuffer.clear(Color::encode(Color::Black));
}

void Canvas::draw(s_t deltaTime) {
	static s_t elapsedTime = deltaTime;
	elapsedTime += deltaTime;

	framebuffer.clear(Color::encode(Color::Black));
	using namespace lmath;

	//Matrix4 worldToCamera = Matrix4::identity;
	Transform camera; // TODO: transform into object
	camera.translate(0, 0, -2);
	camera.rotate_y(elapsedTime);
	float d = .5f;// + (sinf(elapsedTime)+1.0f) / 2.0f;
	Matrix4 projection = Matrix4::identity;
	projection[3][3] = 0;
	projection[3][2] = d;

	Object cube;
	cube.mesh = Mesh::cube;
	cube.transform.translate(2, 0, 0);
	Object cube2;
	cube2.mesh = Mesh::cube;
	cube2.transform = cube.transform;
	cube2.transform.scale(.5f,.5f,.5f);
	cube2.transform.rotate_y(3.141519f/4.0f);

	std::vector<Object> objects;
	objects.push_back(cube);
	objects.push_back(cube2);
	for (std::vector<Object>::iterator object_it = objects.begin(); object_it != objects.end(); ++object_it) {
		std::vector<Vector2> screenPoints;
		for (std::vector<Vector3>::iterator vertex_it = (*object_it).mesh.vertices.begin(); vertex_it != (*object_it).mesh.vertices.end(); ++vertex_it) {
			Vector4 vertex = *vertex_it;
			vertex.w = 1.0f;
			Vector4 worldPoint = (*object_it).transform.matrix * vertex;
			Vector4 cameraPoint = camera.inverse * worldPoint; // camera-> world to camera, not local to world
			//if (cameraPoint.z < 0.0f) continue; //fixme! near clipping
			Vector4 screenPoint = projection * cameraPoint;
			screenPoint /= screenPoint.w;
			screenPoint.x = (screenPoint.x + 1.0f) / 2.0f;
			screenPoint.y = (screenPoint.y + 1.0f) / 2.0f;
			screenPoints.push_back(Vector2(screenPoint.x, screenPoint.y));
		}

		for (auto edge_it = (*object_it).mesh.edges.begin(); edge_it != (*object_it).mesh.edges.end(); edge_it += 2) {
			drawLine(screenPoints[*edge_it], screenPoints[*(edge_it+1)], Color::White);
		}
	}

}



void Canvas::drawPixel(float x, float y, Color color)
{
	//assert(x >= 0.0f && x <= 1.0f);
	//assert(y >= 0.0f && y <= 1.0f);
	static float ratio = width/static_cast<float>(height); // TODO reset when resolution is changed
	static float border = (ratio-1)/2.0f;

	if (x >= -border && x <= ratio-border && y >= 0.0f && y <= 1.0f) { // fixme! not working when vertical > horizontal
		drawPixel(static_cast<int>( (border + x) * (height - 1)), static_cast<int>(y * (height - 1)), color);
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

void Canvas::drawLine(Vector2 v, Vector2 w, Color color) {
	drawLine(v.x, v.y, w.x, w.y, color, color);
}

const FrameBuffer& Canvas::getFramebuffer() const
{
	return framebuffer;
}