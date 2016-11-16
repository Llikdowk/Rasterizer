//
// Created by Llikdowk on 16-Nov-16.
//

#include <gtest/gtest.h>
#include <Matrix4.h>

TEST(matrix, identity_one_zero) {
	using namespace lmath;
	Matrix4 m = Matrix4::identity;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == j) {
				ASSERT_EQ(m.get(i, j), 1);
			} else {
				ASSERT_EQ(m.get(i, j), 0);
			}
		}
	}

	m = Matrix4::one;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			ASSERT_EQ(m.get(i, j), 1);
		}
	}

	m = Matrix4::zero;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			ASSERT_EQ(m.get(i, j), 0);
		}
	}
}

TEST(matrix, modifyValues) {
	lmath::Matrix4 m = lmath::Matrix4::one;
	m.get(0, 1) = 5.5f;
	ASSERT_FLOAT_EQ(m.get(0, 1), 5.5f);
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


}