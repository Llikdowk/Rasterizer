//
// Created by Llikdowk on 16-Nov-16.
//

#include <gtest/gtest.h>
#include <Matrix4.h>
#include <Vector.h>

TEST(matrix, identity_one_zero) {
	using namespace lmath;
	Matrix4 m = Matrix4::identity;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == j) {
				ASSERT_EQ(m.at(i, j), 1);
			} else {
				ASSERT_EQ(m.at(i, j), 0);
			}
		}
	}

	m = Matrix4::one;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			ASSERT_EQ(m.at(i, j), 1);
		}
	}

	m = Matrix4::zero;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			ASSERT_EQ(m.at(i, j), 0);
		}
	}
}

TEST(matrix, modifyValues) {
	lmath::Matrix4 m = lmath::Matrix4::one;
	m.at(0, 1) = 5.5f;
	ASSERT_FLOAT_EQ(m.at(0, 1), 5.5f);

	lmath::Matrix4 q = m;
	q.at(0, 1) = 0.9f;
	ASSERT_FLOAT_EQ(m.at(0, 1), 5.5f);
	ASSERT_FLOAT_EQ(q.at(0, 1), 0.9f);

	std::cout << q[0][3] << std::endl;

}

TEST(matrix, mult) {
	lmath::Matrix4 A = {
			0, -2, 2, 0,
			-1, 3, 1, 0,
			4,  5, 6, 0,
			0,  0, 0, 0
	};

	lmath::Matrix4 B = {
			7,0,8,0,
			2,-2,9,0,
			1,-3,-1,0,
			0,0,0,0
	};

	lmath::Matrix4 C = lmath::Matrix4::one;

	std::cout << A*B << std::endl;
	std::cout << std::endl;
	std::cout << B*A << std::endl;
	std::cout << std::endl;
	std::cout << C*-1.5f << std::endl;

	lmath::Vector4 v(1);
	lmath::Vector4 res = A * v;
	std::cout << res << std::endl;
}