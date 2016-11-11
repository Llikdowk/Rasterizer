//
// Created by Llikdowk on 11-Nov-16.
//

#include "Vector.h"
#include <cmath>

using namespace lmath;


const Vector4 Vector4::zero = Vector4(0, 0, 0, 0);
const Vector4 Vector4::one = Vector4(1, 1, 1, 1);

float Vector4::sqrDistance(const Vector4& v) const {
	return (v.x - x)*(v.x - x) + (v.y - y)*(v.y - y) + (v.z - z) * (v.z - z) + (v.t - t) * (v.t - t);
}

float Vector4::distance(const Vector4& v) const {
	return sqrtf(sqrDistance(v));
}

bool Vector4::operator==(const Vector4& v) const {
	return x == v.x && y == v.y && z == v.z && t == v.t;
}

bool Vector4::operator!=(const Vector4& v) const {
	return !(*this == v);
}