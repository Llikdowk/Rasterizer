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
		using float4x4 = std::array<std::array<float, 4>, 4>;

		static const Matrix4 identity;
		static const Matrix4 one;
		static const Matrix4 zero;

		explicit Matrix4(float f);

		Matrix4(float4 row1, float4 row2, float4 row3, float4 row4);

		Matrix4(
				float a11, float a12, float a13, float a14,
				float a21, float a22, float a23, float a24,
				float a31, float a32, float a33, float a34,
				float a41, float a42, float a43, float a44
		);


		float &at(int, int);
		Matrix4 operator*(const Matrix4 &) const;
		Matrix4 operator*(float) const;
		float4 operator*(const float4 &) const;
		bool operator==(const Matrix4 &) const;
		float4& operator[](int i);

		Matrix4 transpose();

		friend Matrix4 lmath::operator*(float, const Matrix4 &);
		friend std::ostream &operator<<(std::ostream &, const Matrix4 &); //TODO: should not depend on ostream

	private:
		float4x4 data;

		Matrix4() {};
	};
}