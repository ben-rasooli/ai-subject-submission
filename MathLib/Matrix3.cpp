#include "pch.h"
#include "Matrix3.h"


Matrix3::Matrix3()
{
	m[0] = 1; m[3] = 0; m[6] = 0;
	m[1] = 0; m[4] = 1; m[7] = 0;
	m[2] = 0; m[5] = 0; m[8] = 1;
}

Matrix3::Matrix3(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8)
{
	m[0] = m0; m[3] = m3; m[6] = m6;
	m[1] = m1; m[4] = m4; m[7] = m7;
	m[2] = m2; m[5] = m5; m[8] = m8;
}

void Matrix3::setRotateX(float radians)
{
	float co = cosf(radians);
	float si = sinf(radians);

	/*-------*//*-------*//*-------*/
	/*-------*/ m[4] = co; m[7] = -si;
	/*-------*/ m[5] = si; m[8] = co;
}

void Matrix3::setRotateY(float radians)
{
	float co = cosf(radians);
	float si = sinf(radians);

	m[0] = co; /*-------*/ m[6] = si;
	/*-------*//*-------*//*-------*/
	m[2] = -si; /*-------*/ m[8] = co;
}

void Matrix3::setRotateZ(float radians)
{
	float co = cosf(radians);
	float si = sinf(radians);

	m[0] = co; m[3] = -si;/*-------*/
	m[1] = si; m[4] = co; /*-------*/
	/*-------*//*-------*//*-------*/
}

void Matrix3::setRotateZ(Vector2 forward)
{
	// x/right axis
	m[0] = forward.right().x;
	m[1] = forward.right().y;

	// y/forward axis
	m[3] = forward.x;
	m[4] = forward.y;
}

void Matrix3::setPosition(float x, float y)
{
	/*------*//*------*/ m[6] = x;
	/*------*//*------*/ m[7] = y;
	/*------*//*------*//*------*/
}

void Matrix3::setPosition(Vector2 pos)
{
	setPosition(pos.x, pos.y);
}

void Matrix3::setScale(float x, float y)
{
	m[0] = x; m[3] = 0; /*------*/
	m[1] = 0; m[4] = y; /*------*/
	/*------*//*------*//*------*/
}

void Matrix3::setScale(Vector2 scale)
{
	setScale(scale.x, scale.y);
}

Vector2 Matrix3::getPosition()
{
	return Vector2(m[6], m[7]);
}

float Matrix3::getRotation()
{
	return atan2(m[1], m[0]);
}

Vector2 Matrix3::getScale()
{
	return Vector2(m[0], m[4]);
}

Vector2 Matrix3::forward()
{
	return Vector2(m[3], m[4]);
}

Vector2 Matrix3::right()
{
	return Vector2(m[0], m[1]);
}

Matrix3 Matrix3::operator*(Matrix3 & other)
{
	Matrix3 result;

	result.m[0] = (m[0] * other.m[0]) + (m[3] * other.m[1]) + (m[6] * other.m[2]);
	result.m[1] = (m[1] * other.m[0]) + (m[4] * other.m[1]) + (m[7] * other.m[2]);
	result.m[2] = (m[2] * other.m[0]) + (m[5] * other.m[1]) + (m[8] * other.m[2]);

	result.m[3] = (m[0] * other.m[3]) + (m[3] * other.m[4]) + (m[6] * other.m[5]);
	result.m[4] = (m[1] * other.m[3]) + (m[4] * other.m[4]) + (m[7] * other.m[5]);
	result.m[5] = (m[2] * other.m[3]) + (m[5] * other.m[4]) + (m[8] * other.m[5]);

	result.m[6] = (m[0] * other.m[6]) + (m[3] * other.m[7]) + (m[6] * other.m[8]);
	result.m[7] = (m[1] * other.m[6]) + (m[4] * other.m[7]) + (m[7] * other.m[8]);
	result.m[8] = (m[2] * other.m[6]) + (m[5] * other.m[7]) + (m[8] * other.m[8]);

	return result;
}

Vector3 Matrix3::operator*(Vector3 & other)
{
	Vector3 result;

	result.x = (m[0] * other.x) + (m[3] * other.y) + (m[6] * other.z);
	result.y = (m[1] * other.x) + (m[4] * other.y) + (m[7] * other.z);
	result.z = (m[2] * other.x) + (m[5] * other.y) + (m[8] * other.z);

	return result;
}

Vector3& Matrix3::operator[](int columnIndex)
{
	return *((Vector3*)&m[columnIndex * 3]);
}

Matrix3::operator float*()
{
	return m;
}
