#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include "vec4.h"
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
	Mat4 result = Mat4();
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

void Mat4::print()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << this->matrix[i][j] << " ";
		cout << endl;
	}
}

int main () 
{
	Mat4 mat1 = Mat4(1, 2, 3, 4, 2, 2, 3, 2, 3, 1, 1, 3, 1, 2, 2, 4);
	Mat4 mat2 = mat1.inverse();
	mat2.print();
	cout << "Det: " << mat1.det4() << endl;
	//Mat4 res = mat1 * mat2;
	//res.print();
	return 0;
}