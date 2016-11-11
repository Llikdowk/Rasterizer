//
// Created by Llikdowk on 11-Nov-16.
//

#include <gtest/gtest.h>
#include "Vector.h"

#define check custom_math
using namespace lmath;

TEST(check, vector4) {
	Vector4 v(3, -3, 1, 53);
	Vector4 w(v);
	Vector4 a(4, 45, 56, 1);
	EXPECT_EQ(v.distance(w), 0.0f);
	EXPECT_NE(v.distance(a), 0.0f);
}