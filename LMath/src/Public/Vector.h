//
// Created by Llikdowk on 11-Nov-16.
//

#pragma once
#include <ostream>

namespace lmath {

	class Vector3;
	class Vector2;

	class Vector4 {
	public:
		using rad = float;

		static const Vector4 zero;
		static const Vector4 one;

		Vector4(float x, float y, float z, float t) : x(x), y(y), z(z), t(t) {}

		float sqrDistance(const Vector4&) const;
		float distance(const Vector4&) const;
		float dot(const Vector4 &) const;
		float length() const;
		float sqrLength() const;
		Vector4 normal() const;
		void normalize();
		rad angle(const Vector4&) const;


	protected:
		float x, y, z, t;

	public:
		bool operator==(const Vector4&) const;
		bool operator!=(const Vector4&) const;
		Vector4 operator*(float) const;
		void operator*=(float);
		Vector4 operator/(float) const;
		void operator/=(float);
		Vector4 operator+(const Vector4&) const;
		void operator+=(const Vector4&);
		Vector4 operator-(const Vector4&) const;
		void operator-=(const Vector4&);
		friend Vector4 lmath::operator*(float k, const Vector4& v);
		friend std::ostream& lmath::operator<<(std::ostream& os, const Vector4& v); //TODO: should not depend on ostream

		virtual operator Vector3() const;
		virtual operator Vector2() const;
	};


	class Vector3 : public Vector4 {
	public:
		static const Vector3 zero;
		static const Vector3 one;
		Vector3(float x, float y, float z) : Vector4(x, y, z, 0.0f) {}
		Vector3 cross(const Vector3 &) const;
		virtual operator Vector4() const;
		virtual operator Vector2() const override;
		friend std::ostream& lmath::operator<<(std::ostream& os, const Vector3& v); //TODO: should not depend on ostream
	};


	class Vector2 : public Vector4 {
	public:
		static const Vector2 zero;
		static const Vector2 one;
		Vector2(float x, float y) : Vector4(x, y, 0.0f, 0.0f) {}
		virtual operator Vector3() const override;
		virtual operator Vector4() const;
		friend std::ostream& lmath::operator<<(std::ostream& os, const Vector2& v); //TODO: should not depend on ostream
	};

}
