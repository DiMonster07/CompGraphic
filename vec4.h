#pragma once
using namespace std;

class Vec4
{
public:
	float c[4];
	Vec4(float _x = 0, float _y = 0, float _z = 0, float _w = 0)
	{
		c[0] = _x;  c[1] = _y; c[2] = _z; c[3] = _w;
	}
	Vec4 operator+(const Vec4& b);
	Vec4 operator+(const float& b);
	Vec4 operator-(const Vec4& b);
	Vec4 operator*(const Vec4& b);
	Vec4 operator*(const float& b);
	template< typename t >
	Vec4 operator*(const t& b);
	float length ();
	Vec4 normalize ();
	void normalize_in_place ();
	float Dot(Vec4 b);
	Vec4 Cross(Vec4 b);
};

struct Vector3f
{
	float x;
	float y;
	float z;
	Vector3f()
	{
	}
	Vector3f(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
};
