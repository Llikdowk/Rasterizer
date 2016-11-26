//
// Created by Llikdowk on 24-Nov-16.
//

#pragma once
#include <Matrix4.h>

class Transform {
public:
	using rad_t = float;
	Transform& translate(float x, float y, float z);
	Transform& rotate_y(rad_t angle);
	Transform& scale(float x, float y, float z);

	lmath::Matrix4 matrix = lmath::Matrix4::identity;
	lmath::Matrix4 inverse = lmath::Matrix4::identity;
};

