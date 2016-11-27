//
// Created by Llikdowk on 26-Nov-16.
//

#pragma once

#include "Transform.h"
#include "Mesh.h"
#include <vector>

class Object { // TODO: test
public:
	Transform transform;
	Mesh mesh;

	~Object() {
		for (std::vector<Object *>::iterator child_it = children.begin(); child_it != children.end(); ++child_it) {
			(*child_it)->transform.matrix = getMatrix();
			(*child_it)->transform.inverse = getInverseMatrix();
			(*child_it)->parent = this->parent;
		}
	}

	void setParent(Object* parent) {
		this->parent = parent;
		Object* p = this;
		parent->children.push_back(p);
	}

	Matrix4 getMatrix() {
		return parent->transform.matrix * transform.matrix;
	}

	Matrix4 getInverseMatrix() {
		return transform.inverse * parent->transform.inverse;
	}

	static const Object nullObject;

private:
	const Object* parent = &nullObject;
	std::vector<Object*> children;
};

