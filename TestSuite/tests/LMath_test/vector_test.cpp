//
// Created by Llikdowk on 11-Nov-16.
//

#include <gtest/gtest.h>
#include "Vector.h"

using namespace lmath;

TEST(vector4, distance) {
	Vector4 v(3, -3, 1, 53);
	Vector4 w(v);
	Vector4 a(4, 45, 56, 1);
	EXPECT_EQ(v.distance(w), 0.0f);
	EXPECT_NE(v.distance(a), 0.0f);

	v = Vector4(-5.2f,3.8f, 4.0f, 29.0f);
	w = Vector4(8.7f,-4.1f, -2.0f, -49.0f);
	const float result = 79.8475f;
	const float value = v.distance(w);
	EXPECT_FLOAT_EQ(value, result);

	const float sqrResult = 6375.6201f;
	const float sqrValue = v.sqrDistance(w);
	EXPECT_FLOAT_EQ(sqrValue, sqrResult);
}

TEST(vector4, length) {
	Vector4 v = Vector4::one;
	EXPECT_EQ(v.length(), sqrtf(4));
	EXPECT_EQ(v.sqrLength(), 4);
}

TEST(vector4, angle) {
	Vector4 v(1, 0, 0, 0);
	Vector4 w(0, 1, 0, 0);
	EXPECT_FLOAT_EQ(v.angle(w), M_PI/2.0f);
	EXPECT_FLOAT_EQ(v.angle(w), w.angle(v));
	w = Vector4(0, 0, 1, 0);
	EXPECT_FLOAT_EQ(v.angle(w), M_PI/2.0f);
	w = Vector4(0, 0, 0, 1);
	EXPECT_FLOAT_EQ(v.angle(w), M_PI/2.0f);
}

TEST(vector4, dot) {
	Vector4 v(2, -1, 5, 23);
	Vector4 w(-1, 2, 8, 1);
	float result = 59.0f;
	EXPECT_FLOAT_EQ(v.dot(w), result);
	EXPECT_FLOAT_EQ(v.dot(w), v.length()*w.length()*cos(v.angle(w)));
}

TEST(vector4, normal) {
	Vector4 v = Vector4::one;
	Vector4 vn = v.normal();
	Vector4 result(0.5f, 0.5f, 0.5f, 0.5f);
	EXPECT_EQ(vn, result);
	vn = vn.normal();
	EXPECT_EQ(vn, result);

	EXPECT_NE(v, result);
	v.normalize();
	EXPECT_EQ(v, result);
}

TEST(vector3, cross)
{
	Vector3 a(3, -3, 1);
	Vector3 b(4, 9, 2);
	Vector3 result(-15, -2, 39);
	EXPECT_EQ(a.cross(b), result);

	Vector4 v(4, 9, 2, 5);
	EXPECT_EQ(a.cross(v), result);
}

TEST(vector4, arithmetics) {
	Vector4 a4 = Vector4::one;
	float k = 4.0f;
	EXPECT_EQ(a4*k, Vector4(4,4,4,4));
	EXPECT_EQ(a4/k, Vector4(.25,.25,.25,.25));
	Vector4 aux = a4;
	aux *= k;
	EXPECT_EQ(aux, Vector4(4,4,4,4));
	aux = a4;
	aux /= k;
	EXPECT_EQ(aux, Vector4(.25,.25,.25,.25));

	Vector4 a(1, 2, 3, 4);
	Vector4 b(-1, -2, -3, -4);
	EXPECT_EQ(a + b, Vector4::zero);
	a += b;
	EXPECT_EQ(a, Vector3::zero);
	a += b;
	EXPECT_EQ(a, b);
	EXPECT_EQ(a - b, Vector3::zero);
	a -= b;
	EXPECT_EQ(a, Vector3::zero);
}

TEST(vector_mixed, arithmetics) {
	Vector3 a(3, 4, 5);
	Vector4 b(-3, -4, -5, -999);
	EXPECT_EQ(a + b, Vector4(0, 0, 0, -999));
	EXPECT_NE(a + b, Vector3::zero);
}
