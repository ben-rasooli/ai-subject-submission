#include "pch.h"
#include "Matrix4.h"


Matrix4::Matrix4()
{
	m[0] = 1; m[4] = 0;  m[8] = 0; m[12] = 0;
	m[1] = 0; m[5] = 1;  m[9] = 0; m[13] = 0;
	m[2] = 0; m[6] = 0; m[10] = 1; m[14] = 0;
	m[3] = 0; m[7] = 0; m[11] = 0; m[15] = 1;
}

Matrix4::Matrix4(
	float m0, float m1, float m2, float m3,
	float m4, float m5, float m6, float m7,
	float m8, float m9, float m10, float m11,
	float m12, float m13, float m14, float m15)
{
	m[0] = m0; m[4] = m4;  m[8] = m8;  m[12] = m12;
	m[1] = m1; m[5] = m5;  m[9] = m9;  m[13] = m13;
	m[2] = m2; m[6] = m6; m[10] = m10; m[14] = m14;
	m[3] = m3; m[7] = m7; m[11] = m11; m[15] = m15;
}

void Matrix4::setRotateX(float radians)
{
	float co = cosf(radians);
	float si = sinf(radians);

	/*-------*//*-------*//*-------*//*-------*/
	/*-------*/ m[5] = co; m[9] =-si;/*-------*/
	/*-------*/ m[6] = si; m[10]= co;/*-------*/
	/*-------*//*-------*//*-------*//*-------*/
}

void Matrix4::setRotateY(float radians)
{
	float co = cosf(radians);
	float si = sinf(radians);

	m[0] = co; /*-------*/ m[8] = si;/*-------*/
	/*-------*//*-------*//*-------*//*-------*/
	m[2] =-si; /*-------*/ m[10]= co;/*-------*/
	/*-------*//*-------*//*-------*//*-------*/
}

void Matrix4::setRotateZ(float radians)
{
	float co = cosf(radians);
	float si = sinf(radians);

	m[0] = co; m[4] =-si; /*-------*//*-------*/
	m[1] = si; m[5] = co; /*-------*//*-------*/
	/*-------*//*-------*//*-------*//*-------*/
	/*-------*//*-------*//*-------*//*-------*/
}

void Matrix4::setPosition(float x, float y, float z)
{
	/*------*//*------*//*------*/m[12] = x;
	/*------*//*------*//*------*/m[13] = y;
	/*------*//*------*//*------*/m[14] = z;
	/*------*//*------*//*------*//*------*/
}

void Matrix4::setPosition(Vector3 pos)
{
	setPosition(pos.x, pos.y, pos.z);
}

void Matrix4::setScale(float x, float y, float z)
{
	m[0] = x; m[4] = 0; m[8] = 0; /*------*/
	m[1] = 0; m[5] = y; m[9] = 0; /*------*/
	m[2] = 0; m[6] = 0; m[10]= z; /*------*/
	/*------*//*------*//*------*//*------*/
}

void Matrix4::setScale(Vector3 scale)
{
	setScale(scale.x, scale.y, scale.z);
}

Vector3 Matrix4::getPosition()
{
	return Vector3();
}

Vector3 Matrix4::getRotation()
{
	Vector3 result;

	/*result.x = atan2(m[6], m[10]);
	result.y = atan2(-m[2], sqrtf(powf(m[6], 2) + powf(m[10], 2)));
	result.z = atan2(m[1], m[0]);*/

	return result;
}

Vector3 Matrix4::getScale()
{
	return Vector3(m[0], m[5], m[10]);
}

Matrix4 Matrix4::operator*(Matrix4 & other)
{
	Matrix4 result;

	result.m[0] = (m[0] * other.m[0]) + (m[4] * other.m[1]) + (m[8] * other.m[2]) + (m[12] * other.m[3]);
	result.m[1] = (m[1] * other.m[0]) + (m[5] * other.m[1]) + (m[9] * other.m[2]) + (m[13] * other.m[3]);
	result.m[2] = (m[2] * other.m[0]) + (m[6] * other.m[1]) + (m[10] * other.m[2]) + (m[14] * other.m[3]);
	result.m[3] = (m[3] * other.m[0]) + (m[7] * other.m[1]) + (m[11] * other.m[2]) + (m[15] * other.m[3]);

	result.m[4] = (m[0] * other.m[4]) + (m[4] * other.m[5]) + (m[8] * other.m[6]) + (m[12] * other.m[7]);
	result.m[5] = (m[1] * other.m[4]) + (m[5] * other.m[5]) + (m[9] * other.m[6]) + (m[13] * other.m[7]);
	result.m[6] = (m[2] * other.m[4]) + (m[6] * other.m[5]) + (m[10] * other.m[6]) + (m[14] * other.m[7]);
	result.m[7] = (m[3] * other.m[4]) + (m[7] * other.m[5]) + (m[11] * other.m[6]) + (m[15] * other.m[7]);

	result.m[8] = (m[0] * other.m[8]) + (m[4] * other.m[9]) + (m[8] * other.m[10]) + (m[12] * other.m[11]);
	result.m[9] = (m[1] * other.m[8]) + (m[5] * other.m[9]) + (m[9] * other.m[10]) + (m[13] * other.m[11]);
	result.m[10] = (m[2] * other.m[8]) + (m[6] * other.m[9]) + (m[10] * other.m[10]) + (m[14] * other.m[11]);
	result.m[11] = (m[3] * other.m[8]) + (m[7] * other.m[9]) + (m[11] * other.m[10]) + (m[15] * other.m[11]);

	result.m[12] = (m[0] * other.m[12]) + (m[4] * other.m[13]) + (m[8] * other.m[14]) + (m[12] * other.m[15]);
	result.m[13] = (m[1] * other.m[12]) + (m[5] * other.m[13]) + (m[9] * other.m[14]) + (m[13] * other.m[15]);
	result.m[14] = (m[2] * other.m[12]) + (m[6] * other.m[13]) + (m[10] * other.m[14]) + (m[14] * other.m[15]);
	result.m[15] = (m[3] * other.m[12]) + (m[7] * other.m[13]) + (m[11] * other.m[14]) + (m[15] * other.m[15]);

	return result;
}

Vector4 Matrix4::operator*(Vector4 & other)
{
	Vector4 result;

	result.x = (m[0] * other.x) + (m[4] * other.y) + (m[8] * other.z) + (m[12] * other.w);
	result.y = (m[1] * other.x) + (m[5] * other.y) + (m[9] * other.z) + (m[13] * other.w);
	result.z = (m[2] * other.x) + (m[6] * other.y) + (m[10] * other.z) + (m[14] * other.w);
	result.w = (m[3] * other.x) + (m[7] * other.y) + (m[11] * other.z) + (m[15] * other.w);

	return result;
}

Vector4& Matrix4::operator[](int columnIndex)
{
	return *((Vector4*)&m[columnIndex * 4]);
}

Matrix4::operator float*()
{
	return m;
}
