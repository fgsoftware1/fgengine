#pragma once
#ifndef Matrix3_HPP
#define Matrix3_HPP

#include "Vector3.hpp"

namespace fgengine
{
	namespace math{
		class Matrix3
		{
		private:
		public:
			float matrixData[9]={0.0};

			Matrix3();

			Matrix3(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8);

			~Matrix3();

			void operator+=(const Matrix3 & m);
			void operator*=(float s);
			void operator*=(const Matrix3 & m);

			Matrix3 operator=(const Matrix3 & value);
			Matrix3 operator+(const Matrix3 & m) const;
			Matrix3 operator*(float s);
			Matrix3 operator*(const Matrix3 & m) const;

			Vector3 operator*(const Vector3 & v) const;

			void setMatrixAsIdentityMatrix();
			void invertMatrix();
			void invertAndTransposeMatrix();
			void show();
			void setMatrixAsInverseOfGivenMatrix(const Matrix3 & m);
			void setMatrixAsTransposeOfGivenMatrix(const Matrix3 & m);
			void makeRotationMatrixAboutXAxisByAngle(float uAngle);
			void makeRotationMatrixAboutYAxisByAngle(float uAngle);
			void makeRotationMatrixAboutZAxisByAngle(float uAngle);
			void transformMatrixAboutXAxisByAngle(float uAngle);
			void transformMatrixAboutYAxisByAngle(float uAngle);
			void transformMatrixAboutZAxisByAngle(float uAngle);

			Matrix3 getInverseOfMatrix() const;
			Matrix3 getTransposeOfMatrix() const;

			Vector3 transformVectorByMatrix(const Vector3 & v) const;

			float getMatrixDeterminant() const;
		};
	}
}

#endif
