#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include "mat4.h"
#include <set>

using namespace std;

Mat4::Mat4(float x11, float x12, float x13, float x14, 
	       float x21, float x22, float x23, float x24, 
	       float x31, float x32, float x33, float x34,
	       float x41, float x42, float x43, float x44)
{
	this->matrix[0][0] = x11; this->matrix[0][1] = x12; this->matrix[0][2] = x13; this->matrix[0][3] = x14;
	this->matrix[1][0] = x21; this->matrix[1][1] = x22; this->matrix[1][2] = x23; this->matrix[1][3] = x24;
	this->matrix[2][0] = x31; this->matrix[2][1] = x32; this->matrix[2][2] = x33; this->matrix[2][3] = x34;
	this->matrix[3][0] = x41; this->matrix[3][1] = x42; this->matrix[3][2] = x43; this->matrix[3][3] = x44;  
}

Mat4::Mat4(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3, const Vec4 &v4)
{
	this->matrix[0][0] = v1.c[0]; this->matrix[0][1] = v1.c[1]; this->matrix[0][2] = v1.c[2]; this->matrix[0][3] = v1.c[3];
	this->matrix[1][0] = v2.c[0]; this->matrix[1][1] = v2.c[1]; this->matrix[1][2] = v2.c[2]; this->matrix[1][3] = v2.c[3];
	this->matrix[2][0] = v3.c[0]; this->matrix[2][1] = v3.c[1]; this->matrix[2][2] = v3.c[2]; this->matrix[2][3] = v3.c[3];
	this->matrix[3][0] = v4.c[0]; this->matrix[3][1] = v4.c[1]; this->matrix[3][2] = v4.c[2]; this->matrix[3][3] = v4.c[3];
}

Mat4 Mat4::operator+(const Mat4& b)
{
	Mat4 result = Mat4();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.matrix[i][j] = this->matrix[i][j] + b.matrix[i][j];
	return result;
}

Mat4 Mat4::operator-(const Mat4& b)
{
	Mat4 result = Mat4();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.matrix[i][j] = this->matrix[i][j] - b.matrix[i][j];
	return result;
}

Mat4 Mat4::operator*(const Mat4& b)
{
    Mat4 result = Mat4();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.matrix[i][j] = this->matrix[i][0] * b.matrix[0][j] + this->matrix[i][1] * b.matrix[1][j] +
		                          this->matrix[i][2] * b.matrix[2][j] + this->matrix[i][3] * b.matrix[3][j];
	return result;
}

Vec4 Mat4::operator*(const Vec4& b)
{
    Vec4 result = Vec4();
	result.c[0] = this->matrix[0][0] * b.c[0] + this->matrix[0][1] * b.c[1] +
			    this->matrix[0][2] * b.c[2] + this->matrix[0][3] * b.c[3];
	result.c[1] = this->matrix[1][0] * b.c[0] + this->matrix[1][1] * b.c[1] +
			    this->matrix[1][2] * b.c[2] + this->matrix[1][3] * b.c[3];
	result.c[2] = this->matrix[2][0] * b.c[0] + this->matrix[2][1] * b.c[1] +
			    this->matrix[2][2] * b.c[2] + this->matrix[2][3] * b.c[3];
	result.c[3] = this->matrix[3][0] * b.c[0] + this->matrix[3][1] * b.c[1] +
			    this->matrix[3][2] * b.c[2] + this->matrix[3][3] * b.c[3];
	return result;
}

template< typename t > 
Mat4 Mat4::operator*(const t& b)
{
	Mat4 result = Mat4();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.matrix[i][j] = this->matrix[i][j] * b;
	return result;
}

template< typename t >
Mat4 Mat4::operator/(const t& b)
{
	if (b == 0) return Mat4();
	Mat4 result = Mat4();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.matrix[i][j] = this->matrix[i][j] / b;
	return result;
}

Mat4 Mat4::ident() {
	Mat4 result = Mat4();
	for(int i = 0; i < 4; i++)
			for(int j = 0; j < 4; j++)
				result.matrix[i][j] = i == j ? 1. : 0.;
	return result;
}

Mat4 Mat4::createIdentity()
{
	Mat4 result = Mat4();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.matrix[i][j] = this->matrix[i][j];
	return result;
}

Mat4 Mat4::transpose ()
{
	Mat4 result = Mat4();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.matrix[i][j] = this->matrix[j][i];
	return result;
}

Mat4 Mat4::perspective(float fovy, float aspect, float near, float far)
{
	fovy = M_PI / 180 * fovy;
	float left, right, bottom, top;
	top = near * tan(fovy / 2);
	bottom = -top;
	right = top * aspect;
	left = -right;
	Mat4 temp = Mat4();
	temp.matrix[0][0] = (2 * near) / (right - left);
	temp.matrix[0][2] = (right + left) / (right - left);
	temp.matrix[1][1] = (2 * near) / (top - bottom);
	temp.matrix[1][2] = (top + bottom) / (top - bottom);
	temp.matrix[2][2] = -(far + near) / (far - near);
	temp.matrix[2][3] = -(2 * far * near) / (far - near);
	temp.matrix[3][2] = -1;
	return temp*(*this);
}

Mat4 Mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
{
	Mat4 temp = Mat4().ident();
	temp.matrix[0][0] = 2.0f / (right - left);
	temp.matrix[1][1] = 2.0f / (top - bottom);
	temp.matrix[2][2] = -2.0f / (far - near);
	temp.matrix[3][3] = 1.0f;
	temp.matrix[0][3] = -(right + left) / (right - left);
	temp.matrix[1][3] = -(top + bottom) / (top - bottom);
	temp.matrix[2][3] = -(far + near) / (far - near);
	return temp*(*this);
}

float Mat4::det2(int c1, int c2, int r1, int r2)
{
	return this->matrix[c1][r1]*this->matrix[c2][r2] - this->matrix[c2][r1]*this->matrix[c1][r2];
}

float Mat4::det3(int c1, int c2, int c3, int r1, int r2, int r3)
{
    float result = 0;
    result = this->matrix[c1][r1]*this->matrix[c2][r2]*this->matrix[c3][r3] + this->matrix[c2][r1]*this->matrix[c3][r2]*this->matrix[c1][r3] +
		     this->matrix[c3][r1]*this->matrix[c1][r2]*this->matrix[c2][r3] - this->matrix[c1][r3]*this->matrix[c2][r2]*this->matrix[c3][r1] -
		     this->matrix[c2][r3]*this->matrix[c3][r2]*this->matrix[c1][r1] - this->matrix[c3][r3]*this->matrix[c1][r2]*this->matrix[c2][r1];
    return result;
}

float Mat4::det4()
{
	float result = 0;
	result += this->matrix[0][0]*this->det3(1, 2, 3, 1, 2, 3);
	result -= this->matrix[0][1]*this->det3(1, 2, 3, 0, 2, 3);
	result += this->matrix[0][2]*this->det3(1, 2, 3, 0, 1, 3);
	result -= this->matrix[0][3]*this->det3(1, 2, 3, 0, 1, 2);
	return result;
}

Mat4 Mat4::inverse()
{
	Mat4 result = Mat4().ident();
	float det = det4();
	result.matrix[0][0] =  det3(1, 2, 3, 1, 2, 3)/det;
	result.matrix[0][1] = -det3(0, 2, 3, 1, 2, 3)/det;
	result.matrix[0][2] =  det3(0, 1, 3, 1, 2, 3)/det;
	result.matrix[0][3] = -det3(0, 1, 2, 1, 2, 3)/det;
	result.matrix[1][0] = -det3(1, 2, 3, 0, 2, 3)/det;
	result.matrix[1][1] =  det3(0, 2, 3, 0, 2, 3)/det;
	result.matrix[1][2] = -det3(0, 1, 3, 0, 2, 3)/det;
	result.matrix[1][3] =  det3(0, 1, 2, 0, 2, 3)/det;
	result.matrix[2][0] =  det3(1, 2, 3, 0, 1, 3)/det;
	result.matrix[2][1] = -det3(0, 2, 3, 0, 1, 3)/det;
	result.matrix[2][2] =  det3(0, 1, 3, 0, 1, 3)/det;
	result.matrix[2][3] = -det3(0, 1, 2, 0, 1, 3)/det;
	result.matrix[3][0] = -det3(1, 2, 3, 0, 1, 2)/det;
    result.matrix[3][1] =  det3(0, 2, 3, 0, 1, 2)/det;
	result.matrix[3][2] = -det3(0, 1, 3, 0, 1, 2)/det;
	result.matrix[3][3] =  det3(0, 1, 2, 0, 1, 2)/det;
	return result;
}

Mat4 Mat4::perspective(Vec4 v) {
	return Mat4(
			Vec4(1.0f, 0.0f, 0.0f, v.c[0]),
			Vec4(0.0f, 1.0f, 0.0f, v.c[1]),
			Vec4(0.0f, 0.0f, 1.0f, v.c[2]),
			Vec4(0.0f, 0.0f, 0.0f, 1.0f))*(*this);
}

Mat4 Mat4::translate(Vec4 v) {
	return Mat4(
			Vec4(1.0f, 0.0f, 0.0f, 0.0f),
			Vec4(0.0f, 1.0f, 0.0f, 0.0f),
			Vec4(0.0f, 0.0f, 1.0f, 0.0f),
			Vec4(v.c[0], v.c[1], v.c[2], 1.0f))*(*this);
}

Mat4 Mat4::scale(Vec4 v) {
	return Mat4(
		    Vec4(v.c[0], 0.0f, 0.0f, 0.0f),
			Vec4(0.0f, v.c[1], 0.0f, 0.0f),
			Vec4(0.0f, 0.0f, v.c[2], 0.0f),
			Vec4(0.0f, 0.0f, 0.0f,   1.0f))*(*this);
}

Mat4 Mat4::rotate(Vec4 v, float angle) {
	Mat4 general_rotation = Mat4::ident();
	angle = angle/180.*M_PI;
	if (fabs(v.c[0]) >= epsilon)
	{
		general_rotation = general_rotation * Mat4(
				Vec4(1.0f, 0.0f, 0.0f, 0.0f),
				Vec4(0.0f, cos(angle), -sin(angle), 0.0f),
				Vec4(0.0f, sin(angle),  cos(angle), 0.0f),
				Vec4(0.0f, 0.0f, 0.0f, 1.0f));
	}
	if (fabs(v.c[1]) >= epsilon)
	{
		general_rotation = general_rotation * Mat4(
				Vec4(cos(angle), 0.0f, sin(angle), 0.0f),
				Vec4(0.0f, 1.0f, 0.0f, 0.0f),
				Vec4(-sin(angle), 0.0f, cos(angle), 0.0f),
				Vec4(0.0f, 0.0f, 0.0f, 1.0f));

	}
	if (fabs(v.c[2]) >= epsilon)
	{
		general_rotation = general_rotation * Mat4(
				Vec4(cos(angle), -sin(angle), 0.0f, 0.0f),
				Vec4(sin(angle),  cos(angle), 0.0f, 0.0f),
				Vec4(0.0f, 0.0f, 1.0f, 0.0f),
				Vec4(0.0f, 0.0f, 0.0f, 1.0f));

	}
	return general_rotation*(*this);
}

void Mat4::print()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << this->matrix[i][j] << " ";
		cout << endl;
	}
}
