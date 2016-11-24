//
// Created by Llikdowk on 11-Nov-16.
//

#include "Vector.h"
#include <cmath>
#include <assert.h>

using namespace lmath;


const Vector4 Vector4::zero = Vector4(0, 0, 0, 0);
const Vector4 Vector4::one = Vector4(1, 1, 1, 1);
const Vector3 Vector3::zero = Vector3(0,0,0);
const Vector3 Vector3::one = Vector3(1,1,1);
const Vector2 Vector2::zero = Vector2(0,0);
const Vector2 Vector2::one = Vector2(1,1);

Vector4::Vector4(float x, float y, float z, float w)
		: x(data[0]), y(data[1]), z(data[2]), w(data[3])
{
	data = {x, y, z, w};
}


Vector4::Vector4(const Vector4& v)
		: data(v.data), x(data[0]), y(data[1]), z(data[2]), w(data[3])
{
}

Vector4::Vector4(const float4& d)
		: data(d), x(data[0]), y(data[1]), z(data[2]), w(data[3])
{
}


float Vector4::sqrDistance(const Vector4& v) const {
	return (v.x - x)*(v.x - x) + (v.y - y)*(v.y - y) + (v.z - z) * (v.z - z) + (v.w - w) * (v.w - w);
}

float Vector4::distance(const Vector4& v) const {
	return sqrtf(sqrDistance(v));
}

bool Vector4::operator==(const Vector4& v) const {
	const static float epsilon = 0.0001f;
	bool isEqual = true;

	for (int i = 0; i < 4; ++i) {
		if (!isEqual) break;
		if (v.data[i] == 0.0f && data[i] == 0.0f) continue;
		isEqual = isEqual && fabs(v.data[i] - data[i])/std::max(fabs(v.data[i]), fabs(data[i])) < epsilon;
	}

	return isEqual;
}

bool Vector4::operator!=(const Vector4& v) const {
	return !(*this == v);
}

float Vector4::dot(const Vector4 &v) const {
	return v.x*x + v.y*y + v.z*z + v.w*w;
}

float Vector4::length() const {
	return sqrtf(x*x + y*y + z*z + w*w);
}

float Vector4::sqrLength() const {
	return x*x + y*y + z*z + w*w;
}

Vector4 Vector4::normal() const {
	return *this/length();
}

void Vector4::normalize() {
	*this = *this/length();
}

auto Vector4::angle(const Vector4& v) const -> rad{
	return acosf(dot(v)/(length() * v.length()));
}

Vector3 Vector3::cross(const Vector3& v) const {
	return Vector3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}


Vector4& Vector4::operator=(const Vector4& v) {
	this->data = v.data;
	return *this;
}

Vector4::operator Vector3() const {
	return Vector3(x, y, z);
}

Vector4::operator Vector2() const {
	return Vector2(x, y);
}

Vector3::operator Vector4() const {
	return Vector4(x, y, z, 0.0f);
}

Vector3::operator Vector2() const {
	return Vector2(x, y);
}

Vector2::operator Vector3() const {
	return Vector3(x, y, 0.0f);
}

Vector2::operator Vector4() const {
	return Vector4(x, y, 0.0f, 0.0f);
}


Vector4 Vector4::operator*(float k) const {
	return Vector4(x * k, y * k, z * k, w * k);
}

void Vector4::operator*=(float k) {
	*this = *this * k;
}

Vector4 Vector4::operator/(float k) const {
	return (*this) * (1.0f / k);
}

void Vector4::operator/=(float k) {
	*this = *this / k;
}

Vector4 Vector4::operator+(const Vector4& v) const {
	return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
}

void Vector4::operator+=(const Vector4& v) {
	*this = *this + v;
}

Vector4 Vector4::operator-(const Vector4& v) const {
	return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
}

void Vector4::operator-=(const Vector4& v) {
	*this = *this - v;
}

float& Vector4::operator[](int i) {
	assert(i >= 0 && i < 4);
	return data[i];
}

const float& Vector4::operator[](int i) const {
	assert(i >= 0 && i < 4);
	return data[i];
}

Vector4::operator float4() const {
	return data;
}

namespace lmath
{
	Vector4 operator*(float k, const Vector4 &v) {
		return v * k;
	}

	std::ostream& operator<<(std::ostream& os, const Vector4& v) {
		os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Vector3& v) {
		os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Vector2& v) {
		os << "(" << v.x << ", " << v.y << ")";
		return os;
	}


}


