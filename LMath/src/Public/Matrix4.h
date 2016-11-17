//
// Created by Llikdowk on 16-Nov-16.
//

#pragma once
#include <ostream>
#include <array>
#include <assert.h>

namespace lmath {
	class ProxyAccess;

	class Matrix4 {
	public:
		using float4 = std::array<float, 4>;

		static const Matrix4 identity;
		static const Matrix4 one;
		static const Matrix4 zero;

		Matrix4(
				float a11, float a12, float a13, float a14,
				float a21, float a22, float a23, float a24,
				float a31, float a32, float a33, float a34,
				float a41, float a42, float a43, float a44
		);

		float& at(int, int);



	private:
		float data[4][4];

	public:
		Matrix4 operator*(const Matrix4&) const;
		Matrix4 operator*(float) const;
		float4 operator*(const float4&) const;
		ProxyAccess operator[](int i);

		//friend float4 			lmath::operator*(const float4&, const Matrix4&);
		friend Matrix4 			lmath::operator*(float, const Matrix4&);
		friend std::ostream&	lmath::operator<<(std::ostream&, const Matrix4&); //TODO: should not depend on ostream

	};


	class ProxyAccess { // TODO: check asm created when accessing matrix data using this
	public:
		float& operator[](int j) { assert(j >= 0 && j < 4); return data[j]; }
	private:
		friend class Matrix4;
		ProxyAccess(float* data) : data(data) {}
		float* data;
	};
}