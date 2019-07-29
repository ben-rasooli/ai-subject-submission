#pragma once

struct Vector4
{
	Vector4();
	Vector4(float x, float y, float z, float w);

	float magnitude();
	float magnitudeSqr();
	void normalise();
	Vector4 normalised();
	float dot(const Vector4& other);
	Vector4 cross(const Vector4& other);
	static float angle(Vector4 from, Vector4 to);

	//operstors
	Vector4 operator+(Vector4& other);
	Vector4 operator-(Vector4& other);
	Vector4 operator*(float multiplier);
	Vector4 operator/(float divider);
	Vector4& operator+=(Vector4& other);
	Vector4& operator-=(Vector4& other);
	float& operator[](int index);
	operator float*();

	float x, y, z, w;
};

Vector4 operator*(float multiplier, Vector4 vector2);
