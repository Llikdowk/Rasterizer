//
// Created by Llikdowk on 24-Nov-16.
//

#include "Transform.h"
#include <cmath>

using namespace lmath;
Transform& Transform::translate(float x, float y, float z) {
	Matrix4 forward_translation = {
			1,0,0,x,
			0,1,0,y,
			0,0,1,z,
			0,0,0,1
	};

	Matrix4 backward_translation = {
			1,0,0,-x,
			0,1,0,-y,
			0,0,1,-z,
			0,0,0,1
	};

	inverse = forward_translation*inverse;
	matrix = matrix*backward_translation;
	return *this;
}

Transform& Transform::rotate_y(rad_t angle) {
	Matrix4 forward_rotation = {
			cosf(angle), 0, sinf(angle), 0,
			0, 1, 0, 0,
			-sinf(angle), 0, cosf(angle), 0,
			0, 0, 0, 1
	};

	Matrix4 backward_rotation = {
			cosf(angle), 0, -sinf(angle), 0,
			0, 1, 0, 0,
			sinf(angle), 0, cosf(angle), 0,
			0, 0, 0, 1
	};

	inverse = forward_rotation * inverse;
	matrix = matrix * backward_rotation;
	return *this;
}

Transform& Transform::scale(float x, float y, float z) {
	Matrix4 forward_scale = {
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1
	};

	Matrix4 backward_scale = {
			1.0f/x, 0, 0, 0,
			0, 1.0f/y, 0, 0,
			0, 0, 1.0f/z, 0,
			0, 0, 0, 1
	};

	inverse = forward_scale * inverse;
	matrix = matrix * backward_scale;
	return *this;
}