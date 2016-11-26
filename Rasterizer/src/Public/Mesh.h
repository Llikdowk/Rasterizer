//
// Created by Llikdowk on 24-Nov-16.
//

#pragma once

#include <vector>
#include <Vector.h>

using namespace lmath;
struct Mesh {
	std::vector<Vector3> vertices;
	std::vector<int> edges;
	static const Mesh cube;

	Mesh() {}
	Mesh(std::vector<Vector3> vertices, std::vector<int> edges) : vertices(vertices), edges(edges) {}
};

