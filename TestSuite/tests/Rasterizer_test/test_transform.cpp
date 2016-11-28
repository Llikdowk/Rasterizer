//
// Created by Llikdowk on 25-Nov-16.
//

#include <gtest/gtest.h>

// fixme! shame on me!
#define private public

#include <Vector.h>
#include <Matrix4.h>
#include <Transform.h>

using namespace lmath;
TEST(transform, translation) {
	Transform t;
	t.translate(1, -1, -2);
	Matrix4 ResultWTL = {
			1,0,0,1,
			0,1,0,-1,
			0,0,1,-2,
			0,0,0,1
	};

	Matrix4 ResultLTW = {
			1,0,0,-1,
			0,1,0,1,
			0,0,1,2,
			0,0,0,1
	};

	ASSERT_EQ(t.inverse, ResultWTL);
	ASSERT_EQ(t.matrix, ResultLTW);

	Vector4 w(0,0,0,1);
	ASSERT_EQ(static_cast<Vector4>(t.matrix * w), Vector4(1, -1, -2, 1));

	Vector4 v(1, -1, -2, 1);
	ASSERT_EQ(static_cast<Vector4>(t.inverse*v), w);
}

TEST(transform, scale) {
	Transform t;
	t.scale(2, 5, 10);
	ASSERT_EQ(static_cast<Vector4>(t.matrix * Vector4::one), Vector4(2,5,10,1));
	ASSERT_EQ(static_cast<Vector4>(t.inverse * Vector4(2,5,10,1)), Vector4::one);
}

TEST(transform, rotation) {
	EXPECT_EQ("", "TODO");
}

TEST(transform, composition) {
	Transform t;
	t.translate(432,4.3,-.123f).rotate_y(3.14f).scale(.4f,.5f,.6f).translate(-1,-2,-3);
	ASSERT_EQ(t.inverse*t.matrix, Matrix4::identity);
	ASSERT_EQ(t.matrix*t.inverse, Matrix4::identity);
}