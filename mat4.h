#pragma once
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <set>
#include "vec4.h"

using namespace std;

const float epsilon = 1e-10;

class Mat4
{
public:
	float matrix[4][4];
	Mat4(float x11 = 0, float x12 = 0, float x13 = 0, float x14 = 0, 
		 float x21 = 0, float x22 = 0, float x23 = 0, float x24 = 0, 
		 float x31 = 0, float x32 = 0, float x33 = 0, float x34 = 0,
		 float x41 = 0, float x42 = 0, float x43 = 0, float x44 = 0);
	Mat4(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3, const Vec4 &v4);
	Mat4 operator+(const Mat4& b);
	Mat4 operator-(const Mat4& b);
	Mat4 operator*(const Mat4& b);
	Vec4 operator*(const Vec4& b);
	template< typename t >
	Mat4 operator*(const t& b);
	template< typename t >
	Mat4 operator/(const t& b);
	Mat4 ident();
	Mat4 perspective(Vec4 v);
	Mat4 translate(Vec4 v);
	Mat4 scale(Vec4 v);
	Mat4 rotate(Vec4 v, float angle);
	Mat4 createIdentity();
	Mat4 transpose ();
	Mat4 perspective(float fovy, float aspect, float near, float far);
	Mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
	float det2(int c1, int c2, int r1, int r2);
	float det3(int r1, int r2, int r3, int c1, int c2, int c3);
	float det4();
	Mat4 inverse();
	void print();
};
