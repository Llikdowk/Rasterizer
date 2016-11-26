//
// Created by Llikdowk on 26-Nov-16.
//

#pragma once

#include <vector>
#include "Transform.h"
#include "Mesh.h"

struct Object {
	Object* parent = nullptr;
	std::vector<Object> children;

	Transform transform; // TODO should be private to get transform compound from parents by using a getter
	Mesh mesh;
};

