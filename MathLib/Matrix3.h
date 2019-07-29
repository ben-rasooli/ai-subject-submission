#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include <cmath>

struct Matrix3
{
	Matrix3();
	Matrix3(
		float m0, float m1, float m2,
		float m3, float m4, float m5,
		float m6, float m7, float m8);

	void setRotateX(float radians);
	void setRotateY(float radians);
	void setRotateZ(float radians);
	void setRotateZ(Vector2 forward);

	void setPosition(float x, float y);
	void setPosition(Vector2 pos);

	void setScale(float x, float y);
	void setScale(Vector2 scale);

	Vector2 getPosition();
	float getRotation();
	Vector2 getScale();

	Vector2 forward();
	Vector2 right();

	Matrix3 operator*(Matrix3& other);
	Vector3 operator*(Vector3& other);
	Vector3& operator[](int columnIndex);
	operator float*();

	float m[9];
};

