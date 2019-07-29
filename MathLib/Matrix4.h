#pragma once
#include "Vector3.h"
#include "Vector4.h"
#include <cmath>

struct Matrix4
{
	Matrix4();
	Matrix4(
		float m0, float m1, float m2, float m3,
		float m4, float m5, float m6, float m7,
		float m8, float m9, float m10, float m11,
		float m12, float m13, float m14, float m15);

	void setRotateX(float radians);
	void setRotateY(float radians);
	void setRotateZ(float radians);

	void setPosition(float x, float y, float z);
	void setPosition(Vector3 pos);

	void setScale(float x, float y, float z);
	void setScale(Vector3 scale);

	Vector3 getPosition();
	Vector3 getRotation();
	Vector3 getScale();

	Matrix4 operator*(Matrix4& other);
	Vector4 operator*(Vector4& other);
	Vector4& operator[](int columnIndex);
	operator float*();

	float m[16];
};

