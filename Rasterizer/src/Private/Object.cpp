//
// Created by Llikdowk on 27-Nov-16.
//

#include "Object.h"

const Object Object::nullObject = Object();

Object::~Object() { // TODO read about virtual destructors
	for (std::vector<Object *>::iterator child_it = children.begin(); child_it != children.end(); ++child_it) {
		(*child_it)->transform.matrix = getMatrix();
		(*child_it)->transform.inverse = getInverseMatrix();
		(*child_it)->parent = this->parent;
	}
}

void Object::setParent(Object* parent) {
	this->parent = parent;
	Object* p = this;
	parent->children.push_back(p);
}

Matrix4 Object::getMatrix() {
	return parent->transform.matrix * transform.matrix;
}

Matrix4 Object::getInverseMatrix() {
	return transform.inverse * parent->transform.inverse;
}


Camera::Camera(int width, int height, float d, FrameBuffer* fb)
		:
		Object(),
		width(width),
		height(height),
		projection(
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,d,0
		),
		frameBuffer(fb)
{}

FrameBuffer& Camera::getFrameBuffer() {
	return *frameBuffer;
}


ObjectRenderable::ObjectRenderable(Camera camera)
		: Object(), camera(camera)
{}

void ObjectRenderable::draw() {
	std::vector<Vector2> screenPoints;
		for (std::vector<Vector3>::iterator vertex_it = this->mesh.vertices.begin(); vertex_it != this->mesh.vertices.end(); ++vertex_it) {
			Vector4 vertex = *vertex_it;
			vertex.w = 1.0f;
			Vector4 worldPoint = this->getMatrix() * vertex;
			Vector4 cameraPoint = camera.getInverseMatrix() * worldPoint; // camera-> world to camera, not local to world
			//if (cameraPoint.z < 0.0f) continue; //fixme! near clipping
			Vector4 screenPoint = camera.projection * cameraPoint;
			screenPoint /= screenPoint.w;
			screenPoint.x = (screenPoint.x + 1.0f) / 2.0f;
			screenPoint.y = (screenPoint.y + 1.0f) / 2.0f;
			screenPoints.push_back(Vector2(screenPoint.x, screenPoint.y));
		}

		for (auto edge_it = this->mesh.edges.begin(); edge_it != this->mesh.edges.end(); edge_it += 2) {
			drawLine(screenPoints[*edge_it], screenPoints[*(edge_it+1)], Color::White);
		}
}

void ObjectRenderable::drawPixel(float x, float y, Color color) {
	//assert(x >= 0.0f && x <= 1.0f);
	//assert(y >= 0.0f && y <= 1.0f);
	static float ratio = camera.width/static_cast<float>(camera.height); // TODO reset when resolution is changed
	static float border = (ratio-1)/2.0f;

	if (x >= -border && x <= ratio-border && y >= 0.0f && y <= 1.0f) { // fixme! not working when vertical > horizontal
		drawPixel(static_cast<int>( (border + x) * (camera.height - 1)), static_cast<int>(y * (camera.height - 1)), color);
	}
}

void ObjectRenderable::drawPixel(int x, int y, Color color) {
	camera.getFrameBuffer().setPixel(x, y, Color::encode(color));
}

void ObjectRenderable::drawLine(float xA, float yA, float xB, float yB, Color colorA, Color colorB) {
	float xStep = std::abs((xB - xA) / camera.width);
	float yStep = std::abs((yB - yA) / camera.height);
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

void ObjectRenderable::drawLine(Vector2 v, Vector2 w, Color color) {
	drawLine(v.x, v.y, w.x, w.y, color, color);
}
