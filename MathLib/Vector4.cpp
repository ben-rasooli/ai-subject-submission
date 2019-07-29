#include "pch.h"
#include "Vector4.h"
#include <cmath>
#include <cassert>

Vector4::Vector4()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

float Vector4::magnitude()
{
	return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
}

float Vector4::magnitudeSqr()
{
	return (x * x) + (y * y) + (z * z) + (w * w);
}

void Vector4::normalise()
{
	float mag = magnitude();

	assert(mag != 0 && "normalise: divide by zero");
	if (mag != 0)
	{
		x /= mag;
		y /= mag;
		z /= mag;
		w /= mag;
	}
}

Vector4 Vector4::normalised()
{
	Vector4 result(x, y, z, w);
	result.normalise();
	return result;
}

float Vector4::dot(const Vector4& other)
{
	return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
}

Vector4 Vector4::cross(const Vector4& other)
{
	Vector4 result;

	result.x = (y * other.z) - (z * other.y);
	result.y = (z * other.x) - (x * other.z);
	result.z = (x * other.y) - (y * other.x);
	result.w = 0;

	return result;
}

float Vector4::angle(Vector4 from, Vector4 to)
{
	return acosf(from.dot(to) / (from.magnitude() * to.magnitude()));
}

Vector4 Vector4::operator+(Vector4 & other)
{
	return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vector4 Vector4::operator-(Vector4 & other)
{
	return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

Vector4 Vector4::operator*(float multiplier)
{
	return Vector4(x * multiplier, y * multiplier, z * multiplier, w * multiplier);
}

Vector4 operator*(float multiplier, Vector4 Vector4)
{
	return Vector4 * multiplier;
}

Vector4 Vector4::operator/(float divider)
{
	return Vector4(x / divider, y / divider, z / divider, w / divider);
}

Vector4& Vector4::operator+=(Vector4 & other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;

	return *this;
}

Vector4& Vector4::operator-=(Vector4 & other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;

	return *this;
}

float & Vector4::operator[](int index)
{
	switch (index)
	{
	default:
	case 0: return x;
	case 1: return y;
	case 2: return z;
	case 3: return w;
	}
}

Vector4::operator float*()
{
	return (float*)this;
}
