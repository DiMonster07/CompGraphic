#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include "vec4.h"

using namespace std;

Vec4 Vec4::operator+(const Vec4& b)
{
	return Vec4(this->c[0] + b.c[0], this->c[1] + b.c[1], this->c[2] + b.c[2], this->c[3] + b.c[3]);
}

Vec4 Vec4::operator+(const float& b)
{
	return Vec4(this->c[0] + b, this->c[1] + b, this->c[2] + b, this->c[3] + b);
}

Vec4 Vec4::operator-(const Vec4& b)
{
	return Vec4(this->c[0] - b.c[0], this->c[1] - b.c[1], this->c[2] - b.c[2], this->c[3] - b.c[3]);
}

Vec4 Vec4::operator*(const Vec4& b)
{
	return Vec4(this->c[0] * b.c[0], this->c[1] * b.c[1], this->c[2] * b.c[2], this->c[3] * b.c[3]);
}

template< typename t >
Vec4 Vec4::operator*(const t& b)
{
	return Vec4(this->c[0] * b, this->c[1] * b, this->c[2] * b, this->c[3] * b);
}

Vec4 Vec4::operator*(const float& b)
{
	return Vec4(this->c[0] * b, this->c[1] * b, this->c[2] * b, this->c[3] * b);
}

float Vec4::length (){return sqrt(c[0]*c[0] + c[1]*c[1] + c[2]*c[2]);}

Vec4 Vec4::normalize ()
{
	float l = length();
	return l > 0 ? (Vec4(c[0]/l, c[1]/l, c[2]/l, c[3]/l)) : (Vec4());
};

void Vec4::normalize_in_place ()
{
	float l = length();
	if (l > 0){c[0] /= l; c[1] /= l; c[2] /= l;}
};

float Vec4::Dot(Vec4 b)
{
	return (this->c[0] * b.c[0] + this->c[1] * b.c[1] + this->c[2] * b.c[2]);
};

Vec4 Vec4::Cross(Vec4 b)
{
	return Vec4(this->c[1] * b.c[2] - this->c[2] * b.c[1], - this->c[0] * b.c[2] +
			    this->c[2] * b.c[0], this->c[0] * b.c[1] - this->c[1] * b.c[0], 0);
	//return Vec4(this->c[1] * b.c[2] - this->c[2] * b.c[1], this->c[2] * b.c[0] -
	//		    this->c[0] * b.c[2], this->c[0] * b.c[1] - this->c[1] * b.c[0]);
};
