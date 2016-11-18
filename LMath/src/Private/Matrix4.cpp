//
// Created by Llikdowk on 16-Nov-16.
//

#include "Matrix4.h"

using namespace lmath;

const Matrix4 Matrix4::identity
{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
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

Matrix4::Matrix4(float f)
		:
data{{
		  {{f,f,f,f}},
		  {{f,f,f,f}},
		  {{f,f,f,f}},
		  {{f,f,f,f}}
	  }}
{
	//data.fill({f,f,f,f});
}

Matrix4::Matrix4(float4 row1, float4 row2, float4 row3, float4 row4)
		:
data{{row1, row2, row3, row4}}
{}

Matrix4::Matrix4(
		float a11, float a12, float a13, float a14,
		float a21, float a22, float a23, float a24,
		float a31, float a32, float a33, float a34,
		float a41, float a42, float a43, float a44)
		:
data{{
		 {{a11, a12, a13, a14}},
		 {{a21, a22, a23, a24}},
		 {{a31, a32, a33, a34}},
		 {{a41, a42, a43, a44}}
	 }}
{

	/*
	data = {{
				{a11, a12, a13, a14},
				{a21, a22, a23, a24},
				{a31, a32, a33, a34},
				{a41, a42, a43, a44}
			}};
			*/
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

auto Matrix4::operator*(const float4& v) const -> float4 {
	float4 r;

	for (int i = 0; i < 4; ++i) {
		r[i] = 0;
		for (int j = 0; j < 4; ++j) {
			r[i] += data[i][j] * v[j];
		}
	}

	return r;
}

bool Matrix4::operator==(const Matrix4& m) const {
	float epsilon = 0.001f;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			float temp = data[i][j] - m.data[i][j];
			if (temp > epsilon || temp < -epsilon) {
				return false;
			}
		}
	}
	return true;
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


