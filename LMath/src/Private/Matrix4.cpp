//
// Created by Llikdowk on 16-Nov-16.
//

#include "Matrix4.h"

using namespace lmath;

const Matrix4 Matrix4::identity
{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 1,
		0, 0, 0, 1
};
const Matrix4 Matrix4::one
{
		1, 1, 1, 1,
		1, 1, 1, 1,
		1, 1, 1, 1,
		1, 1, 1, 1
};

const Matrix4 Matrix4::zero
{
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0
};

Matrix4::Matrix4(
		float a11, float a12, float a13, float a14,
		float a21, float a22, float a23, float a24,
		float a31, float a32, float a33, float a34,
		float a41, float a42, float a43, float a44)
{
	data[0][0] = a11;
	data[0][1] = a12;
	data[0][2] = a13;
	data[0][3] = a14;

	data[1][0] = a21;
	data[1][1] = a22;
	data[1][2] = a23;
	data[1][3] = a24;

	data[2][0] = a31;
	data[2][1] = a32;
	data[2][2] = a33;
	data[2][3] = a34;

	data[3][0] = a41;
	data[3][1] = a42;
	data[3][2] = a43;
	data[3][3] = a44;

}

float& Matrix4::at(int i, int j) {
	if(i >= 0 && i < 4 && j >= 0 && j < 4) {
		return data[i][j];
	} else {
		throw std::out_of_range("Access violation in Matrix");
	}
}

Matrix4 Matrix4::operator*(const Matrix4& m) const {
	Matrix4 r = zero;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			r.data[i][j] =
					data[i][0] * m.data[0][j] +
					data[i][1] * m.data[1][j] +
					data[i][2] * m.data[2][j] +
					data[i][3] * m.data[3][j] ;
		}
	}
	return r;
}

Matrix4 Matrix4::operator*(float k) const {
	Matrix4 r = zero;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			r.at(i, j) = data[i][j] * k;
		}
	}
	return r;
}

ProxyAccess Matrix4::operator[](int i) {
	assert(i >= 0 && i < 4);
	return data[i];
}

auto Matrix4::operator*(const float4& v) const -> float4{
	float4 r;

	for (int i = 0; i < 4; ++i) {
		r[i] = 0;
		for (int j = 0; j < 4; ++j) {
			r[i] += data[i][j] * v[j];
		}
	}

	return r;
}

namespace lmath {
	Matrix4 operator*(float k, const Matrix4& M) {
		return M * k;
	}

	std::ostream& operator<<(std::ostream& os, const Matrix4& M) {
		os << std::endl;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				os << M.data[i][j] << "\t\t";
			}
		os << std::endl;
		}
		return os;
	}
}