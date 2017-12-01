#pragma once
#include<cmath>

template<typename T>
class Vec2_
{
public:
	T x;
	T y;
public:
	Vec2_() = default;
	Vec2_(T x1, T y1)
	{
		x = x1;
		y = y1;
	}
	bool operator==(const Vec2_ <T> &v)const
	{
		return this->x == v.x&&this->y == v.y;
	}
	bool operator!=(const Vec2_ <T> &v)const
	{
		return !(*this == v);
	}
	Vec2_<T> operator+ (const Vec2_ <T> &v)const
	{
		return{ x + v.x, y + v.y };
	}
	Vec2_<T> operator- (const Vec2_ <T>&v)const
	{
		return Vec2_(x - v.x, y - v.y);
	}
	Vec2_<T>& operator+=(const Vec2_<T>&v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	Vec2_<T>& operator-=(const Vec2_<T>&v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
	Vec2_<T> operator* (const T p)const
	{
		return Vec2_(x*p, y*p);
	}
	Vec2_<T> operator/ (const T p)const
	{
		return Vec2_(x / p, y / p);
	}
	Vec2_<T>& operator+= (T v)
	{
		x += v;
		y += v;
		return *this;
	}
	Vec2_<T>& operator-= (T v)
	{
		x -= v;
		y -= v;
		return *this;
	}
	Vec2_<T>& operator/=(T v)
	{
		x /= v;
		y /= v;
		return *this;
	}
	float GetLength()
	{
		return sqrt(x*x + y*y);
	}
	Vec2_<T>& Normalize()
	{
		if (GetLength() != 0)
		{
			*this /= GetLength();
		}
		return *this;
	}
};

typedef Vec2_<float> Vec2;
typedef Vec2_<int> Location;