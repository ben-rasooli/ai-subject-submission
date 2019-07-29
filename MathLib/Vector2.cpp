#include "pch.h"
#include "Vector2.h"
#include <cfloat>
#include <cmath>
#include <cassert>

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Vector2::magnitude()
{
	return sqrtf((x * x) + (y * y));
}

float Vector2::magnitudeSqr()
{
	return (x * x) + (y * y);
}

float Vector2::distance(Vector2 other)
{
	Vector2 diff = Vector2(x, y) - other;
	return diff.magnitude();
}

void Vector2::normalise()
{
	float mag = magnitude();

	//assert(mag != 0 && "normalise: divide by zero");
	if (mag != 0)
	{
		x /= mag;
		y /= mag;
	}
}

Vector2 Vector2::normalised()
{
	Vector2 result(x, y);
	result.normalise();
	return result;
}

float Vector2::dot(Vector2& other)
{
	return (x * other.x) + (y * other.y);
}

Vector2 Vector2::right()
{
	return Vector2(y, -x);
}

Vector2 Vector2::left()
{
	return Vector2(-y, x);
}

Vector2 Vector2::lerp(Vector2 startPoint, Vector2 endPoint, float percent)
{
	Vector2 offset = percent * (endPoint - startPoint);
	return startPoint + offset;
}

float Vector2::angle(Vector2 from, Vector2 to)
{
	return acosf(from.dot(to) / (from.magnitude() * to.magnitude()));
}

Vector2 Vector2::zero()
{
	return Vector2(0, 0);
}

Vector2 Vector2::swizzle(char x, char y)
{
	Vector2 result;

	// x component
	switch (x)
	{
	default:
		result.x = x;
		break;
	case 'y':
		result.x = y;
		break;
	}

	// y component
	switch (x)
	{
	default:
		result.y = y;
		break;
	case 'x':
		result.y = x;
		break;
	}

	return result;
}

Vector2 Vector2::operator+(Vector2& other)
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(Vector2& other)
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float multiplier)
{
	return Vector2(x * multiplier, y * multiplier);
}

Vector2 operator*(float multiplier, Vector2 vector2)
{
	return vector2 * multiplier;
}

Vector2 Vector2::operator/(float divider)
{
	return Vector2(x / divider, y / divider);
}

Vector2& Vector2::operator+=(const Vector2 & other)
{
	x += other.x;
	y += other.y;

	return *this;
}

Vector2& Vector2::operator-=(const Vector2 & other)
{
	x -= other.x;
	y -= other.y;

	return *this;
}

bool Vector2::operator==(Vector2 & other)
{
	return approximatelyEqual(x, other.x) && approximatelyEqual(y, other.y);
}

bool Vector2::approximatelyEqual(float a, float b)
{
	return fabs(a - b) <= FLT_EPSILON;
}

float& Vector2::operator[](int index)
{
	switch (index)
	{
	default:
	case 0: return x;
	case 1: return y;
	}
}

Vector2::operator float*()
{
	return (float*)this;
}

Vector2::operator Vector3()
{
	return Vector3(x, y, 0);
}
