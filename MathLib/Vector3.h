#pragma once
#include "Vector4.h"

struct Vector3
{
	Vector3();
	Vector3(float x, float y, float z);

	float magnitude();
	float magnitudeSqr();
	void normalise();
	Vector3 normalised();
	float dot(const Vector3& other);
	Vector3 cross(const Vector3& other);
	static float angle(Vector3 from, Vector3 to);

	//operstors
	Vector3 operator+(Vector3& other);
	Vector3 operator-(Vector3& other);
	Vector3 operator*(float multiplier);
	Vector3 operator/(float divider);
	Vector3& operator+=(Vector3& other);
	Vector3& operator-=(Vector3& other);
	float& operator[](int index);
	operator float*();
	operator Vector4();

	float x, y, z;
};

Vector3 operator*(float multiplier, Vector3 vector2);
