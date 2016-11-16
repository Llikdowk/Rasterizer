//
// Created by Llikdowk on 16-Nov-16.
//

#pragma once
#include <ostream>
#include <assert.h>

namespace lmath {
	class Row;
	class Vector4;

	class Matrix4 {
	public:
		static const Matrix4 identity;
		static const Matrix4 one;
		static const Matrix4 zero;

		Matrix4(
				float a11, float a12, float a13, float a14,
				float a21, float a22, float a23, float a24,
				float a31, float a32, float a33, float a34,
				float a41, float a42, float a43, float a44
		);

		//Matrix4(const float[4][4]);
		//Matrix4(const float[16]);

		float& at(int, int);



	private:
		float data[4][4];

	public:
		Matrix4 operator*(const Matrix4&) const;
		Matrix4 operator*(float) const;
		Vector4 operator*(const Vector4&) const;
		Row operator[](int i);

		//friend Vector4 			lmath::operator*(const Vector4&, const Matrix4&);
		friend Matrix4 			lmath::operator*(float, const Matrix4&);
		friend std::ostream&	lmath::operator<<(std::ostream&, const Matrix4&); //TODO: should not depend on ostream

	};


	class Row { // TODO: check asm created when accessing matrix data using this
	public:
		float& operator[](int j) { assert(j >= 0 && j < 4); return data[j]; }
	private:
		friend class Matrix4;
		Row(float* data) : data(data) {}
		float* data;
	};
}