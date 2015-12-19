#pragma once
#include "vec4.h"

using namespace std;

class Mat4
{
public:
	float matrix[4][4];
	Mat4(float x11 = 0, float x12 = 0, float x13 = 0, float x14 = 0, 
		 float x21 = 0, float x22 = 0, float x23 = 0, float x24 = 0, 
		 float x31 = 0, float x32 = 0, float x33 = 0, float x34 = 0,
		 float x41 = 0, float x42 = 0, float x43 = 0, float x44 = 0);
	Mat4 operator+(const Mat4& b);
	Mat4 operator-(const Mat4& b);
	Mat4 operator*(const Mat4& b);
	template< typename t >
	Mat4 operator*(const t& b);
	template< typename t >
	Mat4 operator/(const t& b);
	Mat4 createIdentity();
	Mat4 transpose ();
	float det2(int c1, int c2, int r1, int r2);
	float det3(int r1, int r2, int r3, int c1, int c2, int c3);
	float det4();
	Mat4 inverse();
	void print();
};
