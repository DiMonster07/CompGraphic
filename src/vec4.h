#pragma once

using namespace std;

class Vec4
{
public:
	float x, y, z, w;
	Vec4(float _x = 0, float _y = 0, float _z = 0, float _w = 0) : x(_x), y(_y), z(_z), w(_w){};
	Vec4 operator+(const Vec4& b);
	Vec4 operator-(const Vec4& b);
	Vec4 operator*(const Vec4& b);
	template< typename t >
	Vec4 operator*(const t& b);
	float length ();
	Vec4 normalize ();
	void normalize_in_place ();
	float Dot(Vec4 b);
	Vec4 Cross(Vec4 b);
};