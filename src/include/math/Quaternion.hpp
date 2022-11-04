#pragma once
#ifndef Quaternion_HPP
#define Quaternion_HPP
#include "Matrix3.hpp"
#include "Vector3.hpp"

namespace fgengine
{
	namespace math{
		class Quaternion
		{
		private:
		public:
			float s;

			Vector3 v;

			Quaternion();

			Quaternion(float uS, Vector3 & uV);

			~Quaternion();

			Quaternion(const Quaternion & value);

			inline Quaternion& operator=(const Quaternion & value);

			void operator+=(const Quaternion & q);
			void operator-=(const Quaternion & q);
			void operator*=(const Quaternion & q);
			void operator*=(float value);

			Quaternion operator+(const Quaternion & q) const;
			Quaternion operator-(const Quaternion & q) const;
			Quaternion operator*(const Quaternion & q) const;
			Quaternion operator*(const Vector3 & uValue) const;
			Quaternion operator*(float value) const;

			void normalize();
			void convertToUnitNormQuaternion();
			void inverse(Quaternion & q);
			void transformEulerAnglesToQuaternion(float x, float y, float z);
			void transformMatrix3ToQuaternion(Matrix3 & uMatrix);
			void show();

			Quaternion multiply(const Quaternion & q) const;
			Quaternion conjugate();
			Quaternion inverse();

			Matrix3 transformQuaternionToMatrix3();

			Vector3 transformQuaternionToEulerAngles();

			float dot(Quaternion & q);
			float norm();
		};
	}
}

#endif
