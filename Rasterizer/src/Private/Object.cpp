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

Matrix4 Object::getMatrix() const {
	return parent->transform.matrix * transform.matrix;
}

Matrix4 Object::getInverseMatrix() const {
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


ObjectRenderable::ObjectRenderable(Camera& camera, const Mesh& mesh)
		: Object(),
		  camera(camera),
		  mesh(mesh),
		  renderer(&(camera.getFrameBuffer()))
{
	//renderer = new NaiveRender(&(camera.getFrameBuffer())); //TODO: analyze this 'new' use properly
}

ObjectRenderable::~ObjectRenderable() {
//	delete renderer;
}

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
			renderer.drawLine(screenPoints[*edge_it], screenPoints[*(edge_it+1)], Color::White);
		}
}

