#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include "vec4.h"

using namespace std;

Vec4 Vec4::operator+(const Vec4& b)
{
	return Vec4(this->x + b.x, this->y + b.y, this->z + b.z, this->w + b.w);
}

Vec4 Vec4::operator-(const Vec4& b)
{
	return Vec4(this->x - b.x, this->y - b.y, this->z - b.z, this->w - b.w);
}

Vec4 Vec4::operator*(const Vec4& b)
{
	return Vec4(this->x * b.x, this->y * b.y, this->z * b.z, this->w * b.w);
}

template< typename t >
Vec4 Vec4::operator*(const t& b)
{
	return Vec4(this->x * b, this->y * b, this->z * b, this->w * b);
}

float Vec4::length (){return sqrt(x*x + y*y + z*z);}

Vec4 Vec4::normalize ()
{
	float l = length();
	return l > 0 ? (Vec4(x/l, y/l, z/l, w)) : (Vec4());
};

void Vec4::normalize_in_place ()
{
	float l = length();
	if (l > 0){x /= l; y /= l; z /= l;}
};

float Vec4::Dot(Vec4 b)
{
	return (this->x * b.x + this->y * b.y + this->z * b.z);
};

Vec4 Vec4::Cross(Vec4 b)
{
	return Vec4(this->y * b.z - this->z * b.y, this->z * b.x - this->x * b.z, this->x * b.y - this->y * b.x);
};

int main ()
{
	Vec4 test = Vec4(1, 2, 3, 4);
	Vec4 test1 = Vec4(4, 3, 2, 1);
	cout << "Res Dot: " << test.Dot(test1) << endl;
	Vec4 res = test.Cross(test1);
	cout << res.x << " " << res.y << " " << res.z << " " << res.w << endl;
	test.normalize_in_place();
	cout << test.y << endl;
	Vec4 test_n = test.normalize();
	cout << test_n.y << endl;
	return 1;
}