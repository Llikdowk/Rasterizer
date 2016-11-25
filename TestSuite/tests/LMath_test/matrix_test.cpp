//
// Created by Llikdowk on 16-Nov-16.
//

#include <gtest/gtest.h>
#include <Matrix4.h>
#include <Vector.h>

using namespace lmath;

TEST(matrix, accessors) {
	Matrix4 m = {
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, 11, 12,
			13, 14, 15, 16
	};

	ASSERT_EQ(m[0][0], 1);
	ASSERT_EQ(m.at(0,0), 1);
	ASSERT_DEBUG_DEATH(m[5][5], "");
	try {
		m.at(5,5);
	} catch(std::out_of_range err) {
		EXPECT_EQ(err.what(), std::string("Access violation in Matrix"));
	}
}

TEST(matrix, identity) {
	Matrix4 m = Matrix4::identity;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == j) {
				ASSERT_EQ(m[i][j], 1);
			}
			else {
				ASSERT_EQ(m[i][j], 0);
			}
		}
	}
}
TEST(matrix, one) {
	Matrix4 m = Matrix4::one;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			ASSERT_EQ(m[i][j], 1);
		}
	}
}
TEST(matrix, zero) {
	Matrix4 m = Matrix4::zero;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			ASSERT_EQ(m[i][j], 0);
		}
	}
}

TEST(matrix, anyNum) {
	Matrix4 m(5);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			ASSERT_EQ(m[i][j], 5);
		}
	}
}

TEST(matrix, randomNum) {
	Matrix4 m = {
			0, 1, 2, 3,
			4, 5, 6, 7,
			8, 9, 10, 11,
			12, 13, 14, 15
	};

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			ASSERT_EQ(m[i][j], i*4 + j);
		}
	}
}

TEST(matrix, modifyValues) {
	lmath::Matrix4 m = lmath::Matrix4::one;
	m[0][1] = 5.5f;
	ASSERT_FLOAT_EQ(m[0][1], 5.5f);

	lmath::Matrix4 q = m;
	q[0][1] = 0.9f;
	ASSERT_FLOAT_EQ(m[0][1], 5.5f);
	ASSERT_FLOAT_EQ(q[0][1], 0.9f);
}

TEST(matrix, mat_mat_mult) {
	Matrix4 A = {{2.25,-1.5f,1.9, 3},{0.1,-2.3f,1.1, 2},{1.02,-2,0.1, 7}, {1.1, 2.2, 3.3, 4.4}};
	Matrix4 B = {{4.25,-2.75f,10.9, 33},{0.15,-12.3f,21.1, 32},{11.02,-2,10.1, 7.25}, {1.2, 62.2, 33.3, 14.45}};
	Matrix4 ResultAB = {{33.8755, 195.063, 111.965, 83.375}, {14.602, 150.215, 30.27, -33.425f}, {13.537, 456.995, 203.028, 71.535}, {46.651, 236.995, 238.26, 194.205}};
	ASSERT_EQ(A*B, ResultAB);
	Matrix4 ResultBA = {{56.7055, 50.75, 115.04, 228.75}, {55.8295, 56.265, 94.465, 264.35}, {42.872, -16.18, 43.673, 131.66}, {58.781, -179.67, 121.715, 424.68}};
	ASSERT_EQ(B*A, ResultBA);
}

TEST(matrix, mat_vec_mult) {
	Matrix4 A = {{2.25,-1.5f,1.9, 3},{0.1,-2.3f,1.1, 2},{1.02,-2,0.1, 7}, {1.1, 2.2, 3.3, 4.4}};
	Vector4 v = {-7, 21.2, 4, -1.1f};
	Vector4 result = {-43.25f, -47.26f, -56.84f, 47.3};
	ASSERT_EQ(static_cast<Vector4>(A*v), result);
}

TEST(matrix, composition) {
	Matrix4 A = {{2.25,-1.5f,1.9, 3},{0.1,-2.3f,1.1, 2},{1.02,-2,0.1, 7}, {1.1, 2.2, 3.3, 4.4}};
	Matrix4 B = {{4.25,-2.75f,10.9, 33},{0.15,-12.3f,21.1, 32},{11.02,-2,10.1, 7.25}, {1.2, 62.2, 33.3, 14.45}};
	Matrix4 R = A*B*B*A*B*A;
	Vector4 v = {-7, 21.2, 4, -1.1f};
	v = R*(R*(R*v));
	Vector4 result(-7.23167e24f, -2.91523e24f, -12.7278e24f, -11.6433e24f);
	ASSERT_EQ(v, result);
}

TEST(matrix, transpose) {
	Matrix4 A = Matrix4::identity;
	ASSERT_EQ(A.transpose(), Matrix4::identity);
	A = {
			+0.718762, -0.393732, +0.573024, 0,
			+0.526967, +0.615033, +0.744416, 0,
			-0.259959, +1.254234, -0.324214, 0,
			+0.539277, +0.777216, -2.53215, 1
	};
	Matrix4 Result = {0.718762, 0.526967,-.259959,0.539277,-0.393732,0.615033,+1.254234,+0.777216,+0.573024,+0.744416, -0.324214,-2.53215, 0,0,0,1};
	ASSERT_EQ(A.transpose(), Result);

	Matrix4 E1 = {0,0,0,1, 0,0,1,0, 1,0,0,0, 0,1,0,0};
	Matrix4 E2 = E1.transpose();
	ASSERT_EQ(E1*E2, Matrix4::identity);
}