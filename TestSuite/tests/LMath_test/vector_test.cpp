//
// Created by Llikdowk on 11-Nov-16.
//

#include <gtest/gtest.h>
#include <cmath>
#include "Vector.h"

using namespace lmath;

TEST(vector4, constructor_multiple_floats) {
	Vector4 v(1,2,3,4);
	for (int i = 0; i < 4; ++i) {
		ASSERT_FLOAT_EQ(v[i], i+1);
	}
}

TEST(vector4, access) {
	Vector4 v {3, 5, 6, 1};
	ASSERT_FLOAT_EQ(v[0], 3);
	ASSERT_FLOAT_EQ(v[1], 5);
	ASSERT_FLOAT_EQ(v[2], 6);
	ASSERT_FLOAT_EQ(v[3], 1);
	ASSERT_EQ(v[0], v.x);
	ASSERT_EQ(v[1], v.y);
	ASSERT_EQ(v[2], v.z);
	ASSERT_EQ(v[3], v.w);
	ASSERT_DEBUG_DEATH(v[4], "");
}

TEST(vector4, constructor_copy) {
	Vector4 v(1,2,3,4);
	Vector4 w = v;
	for (int i = 0; i < 4; ++i) {
		ASSERT_FLOAT_EQ(v[i], w[i]);
		ASSERT_NE(&v[i], &w[i]);
	}
}

TEST(vector4, constructor_float4) {
	Vector4::float4 f4 = {1, 2, 3, 4};
	Vector4 v(f4);
	for (int i = 0; i < 4; ++i) {
		ASSERT_FLOAT_EQ(v[i], i+1);
	}
}


TEST(vector4, distance) {
	Vector4 v(3, -3, 1, 53);
	Vector4 w(v);
	Vector4 a(4, 45, 56, 1);
	ASSERT_EQ(v.distance(w), 0.0f);
	ASSERT_NE(v.distance(a), 0.0f);

	v = Vector4(-5.2f,3.8f, 4.0f, 29.0f);
	w = Vector4(8.7f,-4.1f, -2.0f, -49.0f);
	const float result = 79.8475f;
	const float value = v.distance(w);
	ASSERT_FLOAT_EQ(value, result);

	const float sqrResult = 6375.6201f;
	const float sqrValue = v.sqrDistance(w);
	ASSERT_FLOAT_EQ(sqrValue, sqrResult);
}

TEST(vector4, dot) {
	Vector4 v(2, -1, 5, 23);
	Vector4 w(-1, 2, 8, 1);
	float result = 59.0f;
	ASSERT_FLOAT_EQ(v.dot(w), result);
	ASSERT_FLOAT_EQ(v.dot(w), v.length()*w.length()*cos(v.angle(w)));
}

TEST(vector4, length) {
	Vector4 v(4.5f, 5.25f, -6.11f, 7.12f);
	ASSERT_FLOAT_EQ(v.length(), 11.655f);
	ASSERT_FLOAT_EQ(v.sqrLength(), 135.839025f);
	ASSERT_FLOAT_EQ(v.sqrLength(), v.dot(v));
}

TEST(vector4, angle) {
	Vector4 v(1, 0, 0, 0);
	Vector4 w(0, 1, 0, 0);
	ASSERT_FLOAT_EQ(v.angle(w), M_PI/2.0f);
	ASSERT_FLOAT_EQ(v.angle(w), w.angle(v));
	w = Vector4(0, 0, 1, 0);
	ASSERT_FLOAT_EQ(v.angle(w), M_PI/2.0f);
	w = Vector4(0, 0, 0, 1);
	ASSERT_FLOAT_EQ(v.angle(w), M_PI/2.0f);
}

TEST(vector4, normal) {
	Vector4 v = Vector4::one;
	Vector4 vn = v.normal();
	Vector4 result(0.5f, 0.5f, 0.5f, 0.5f);
	ASSERT_EQ(vn, result);
	vn = vn.normal();
	ASSERT_EQ(vn, result);

	ASSERT_NE(v, result);
	v.normalize();
	ASSERT_EQ(v, result);
}

TEST(vector3, cross)
{
	Vector3 a(3, -3, 1);
	Vector3 b(4, 9, 2);
	Vector3 result(-15, -2, 39);
	ASSERT_EQ(a.cross(b), result);
	Vector4 v(4, 9, 2, 5);
	ASSERT_EQ(a.cross(v), result);
}

TEST(vector4, arithmetics) {
	Vector4 a4 = Vector4::one;
	float k = 4.0f;
	ASSERT_EQ(a4*k, Vector4(4,4,4,4));
	ASSERT_EQ(a4/k, Vector4(.25,.25,.25,.25));
	Vector4 aux = a4;
	aux *= k;
	ASSERT_EQ(aux, Vector4(4,4,4,4));
	aux = a4;
	aux /= k;
	ASSERT_EQ(aux, Vector4(.25,.25,.25,.25));

	Vector4 a(1, 2, 3, 4);
	Vector4 b(-1, -2, -3, -4);
	ASSERT_EQ(a + b, Vector4::zero);
	a += b;
	ASSERT_EQ(a, Vector3::zero);
	a += b;
	ASSERT_EQ(a, b);
	ASSERT_EQ(a - b, Vector3::zero);
	a -= b;
	ASSERT_EQ(a, Vector3::zero);
}

TEST(vector_mixed, arithmetics) {
	Vector3 a(3, 4, 5);
	Vector4 b(-3, -4, -5, -999);
	ASSERT_EQ(a + b, Vector4(0, 0, 0, -999));
	ASSERT_NE(a + b, Vector3::zero);
}
