#include "pch.h"
#include "Vector3.h"
#include <cmath>
#include <cassert>

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vector3::magnitude()
{
	return sqrtf((x * x) + (y * y) + (z * z));
}

float Vector3::magnitudeSqr()
{
	return (x * x) + (y * y) + (z * z);
}

void Vector3::normalise()
{
	float mag = magnitude();

	assert(mag != 0 && "normalise: divide by zero");
	if (mag != 0)
	{
		x /= mag;
		y /= mag;
		z /= mag;
	}
}

Vector3 Vector3::normalised()
{
	Vector3 result(x, y, z);
	result.normalise();
	return result;
}

float Vector3::dot(const Vector3 & other)
{
	return (x * other.x) + (y * other.y) + (z * other.z);
}

Vector3 Vector3::cross(const Vector3& other)
{
	Vector3 result;

	result.x = (y * other.z) - (z * other.y);
	result.y = (z * other.x) - (x * other.z);
	result.z = (x * other.y) - (y * other.x);

	return result;
}

float Vector3::angle(Vector3 from, Vector3 to)
{
	return acosf(from.dot(to) / (from.magnitude() * to.magnitude()));
}

Vector3 Vector3::operator+(Vector3 & other)
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(Vector3 & other)
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(float multiplier)
{
	return Vector3(x * multiplier, y * multiplier, z * multiplier);
}

Vector3 operator*(float multiplier, Vector3 vector3)
{
	return vector3 * multiplier;
}

Vector3 Vector3::operator/(float divider)
{
	return Vector3(x / divider, y / divider, z / divider);
}

Vector3& Vector3::operator+=(Vector3 & other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

Vector3& Vector3::operator-=(Vector3 & other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

float & Vector3::operator[](int index)
{
	switch (index)
	{
	default:
	case 0: return x;
	case 1: return y;
	case 2: return z;
	}
}

Vector3::operator float*()
{
	return (float*)this;
}

Vector3::operator Vector4()
{
	return Vector4(x, y, z, 0);
}
