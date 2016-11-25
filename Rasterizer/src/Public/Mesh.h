//
// Created by Llikdowk on 24-Nov-16.
//

#pragma once
#include <Vector.h>

using namespace lmath;
class Mesh {
public:
	Vector3 vertices[8] = {
			{+0.5f, +0.5f, +0.5f},
			{+0.5f, -0.5f, +0.5f},
			{+0.5f, -0.5f, -0.5f},
			{+0.5f, +0.5f, -0.5f},
			{-0.5f, +0.5f, -0.5f},
			{-0.5f, +0.5f, +0.5f},
			{-0.5f, -0.5f, +0.5f},
			{-0.5f, -0.5f, -0.5f}
	};
/*
	int edges[] = {
			0,3, 3,2, 2,1, 1,0,
			4,7, 7,6, 6,5, 5,4,
			4,3, 5,0,
			7,2, 6,1
	};
	*/

	//void draw();
};

