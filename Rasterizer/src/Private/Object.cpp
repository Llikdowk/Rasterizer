//
// Created by Llikdowk on 27-Nov-16.
//

#include <iostream>
#include "Object.h"

Object::~Object() {
	for (auto child_it = children.begin(); child_it != children.end(); ++child_it) {
		(*child_it)->transform.matrix = getMatrix();
		(*child_it)->transform.inverse = getInverseMatrix();
		(*child_it)->parent = this->parent;
	}

	if (parent != nullptr) {
		auto removed_begin = std::remove(parent->children.begin(), parent->children.end(), this);
		parent->children.erase(removed_begin, parent->children.end());
	}
}

void Object::setParent(Object* parent) {
	this->parent = parent;
	Object* p = this;
	this->parent->children.push_back(p);
	transform.matrix = parent->transform.inverse * transform.matrix;
	transform.inverse = transform.inverse * parent->transform.matrix; // TODO test
}

Matrix4 Object::getMatrix() const {
	if (parent == nullptr) {
		return transform.matrix;
	} else {
		return parent->getMatrix() * transform.matrix;
	}
}

Matrix4 Object::getInverseMatrix() const {
	if (parent == nullptr) {
		return transform.inverse;
	} else {
		return transform.inverse * parent->getInverseMatrix();
	}
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


ObjectRenderable::ObjectRenderable(Camera& camera, const Mesh& mesh)
		: Object(),
		  camera(camera),
		  mesh(mesh),
		  renderer(new NaiveRenderer(camera.getFrameBuffer()))
		  //renderer(new NaiveRenderer(&(camera.getFrameBuffer())))
		  //renderer(&(camera.getFrameBuffer()))
{}

void ObjectRenderable::draw() const {
	std::vector<Vector2> screenPoints;
		for (auto vertex_it = this->mesh.vertices.begin(); vertex_it != this->mesh.vertices.end(); ++vertex_it) {
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
			renderer->drawLine(screenPoints[*edge_it], screenPoints[*(edge_it+1)], Color::White);
		}
}

