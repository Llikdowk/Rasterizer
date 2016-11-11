//
// Created by Llikdowk on 11-Nov-16.
//

#pragma once

namespace lmath {
	class Vector4 {
	public:
		Vector4(float x, float y, float z, float t) : x(x), y(y), z(z), t(t) {}

		float sqrDistance(const Vector4&) const;
		float distance(const Vector4&) const;

		static const Vector4 zero;
		static const Vector4 one;

		bool operator==(const Vector4&) const;
		bool operator!=(const Vector4&) const;

	private:
		float x, y, z, t;
	};

	class Vector3 : public Vector4 {
		Vector3(float x, float y, float z) : Vector4(x, y, z, 0.0f) {};
	};
}
