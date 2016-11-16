//
// Created by Llikdowk on 16-Nov-16.
//

#pragma once
#include <ostream>

namespace lmath {
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

		Matrix4(const float[4][4]);
		Matrix4(const float[16]);
		float& get(int, int);

	private:
		float data[4][4];

	public:
		Matrix4 operator*(const Matrix4&) const;
		Matrix4 operator*(float) const;

		friend Matrix4 			lmath::operator*(float, const Matrix4&);
		friend std::ostream&	lmath::operator<<(std::ostream&, const Matrix4&); //TODO: should not depend on ostream
	};

}