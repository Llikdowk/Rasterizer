//
// Created by Llikdowk on 24-Nov-16.
//

#include "Mesh.h"

const std::vector<Vector3> cube_vertices = {
	{+0.5f, +0.5f, +0.5f},
	{+0.5f, -0.5f, +0.5f},
	{+0.5f, -0.5f, -0.5f},
	{+0.5f, +0.5f, -0.5f},
	{-0.5f, +0.5f, -0.5f},
	{-0.5f, +0.5f, +0.5f},
	{-0.5f, -0.5f, +0.5f},
	{-0.5f, -0.5f, -0.5f}
};

const std::vector<int> cube_edges = {
	0,3, 3,2, 2,1, 1,0,
	4,7, 7,6, 6,5, 5,4,
	4,3, 5,0,
	7,2, 6,1
};

const Mesh Mesh::cube(cube_vertices, cube_edges);