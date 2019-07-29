#pragma once
#include "Vector3.h"

struct Vector2
{
	Vector2();
	Vector2(float x, float y);

	float magnitude();
	float magnitudeSqr();
	float distance(Vector2 other);
	void normalise();
	Vector2 normalised();
	float dot(Vector2& other);
	Vector2 right();
	Vector2 left();
	static Vector2 lerp(Vector2 startPoint, Vector2 endPoint, float percent);
	static float angle(Vector2 from, Vector2 to);
	static Vector2 zero();

	Vector2 swizzle(char x, char y);

	//operstors
	Vector2 operator+(Vector2& other);
	Vector2 operator-(Vector2& other);
	Vector2 operator*(float multiplier);
	Vector2 operator/(float divider);
	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	bool operator==(Vector2& other);
	float& operator[](int index);
	operator float*();
	operator Vector3();

	float x, y;

private:
	bool approximatelyEqual(float a, float b);
};

Vector2 operator*(float multiplier, Vector2 vector2);
