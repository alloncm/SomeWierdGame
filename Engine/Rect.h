#pragma once

#include"Vec2.h"

template<typename T>
class Rect
{
private:
	Vec2_<T> tLeft;
	Vec2_<T> bRight;

public:
	Rect(T x, T y, T w, T h)
		:
		tLeft({ x,y }),
		bRight({ x + w,y + h })
	{}

	Rect(Vec2_<T> tLeft, Vec2_<T> bRight)
		:
		tLeft(tLeft),
		bRight(bRight)
	{}

	Rect()=default;

	Rect(const Rect& r) = default;

	Rect(T width, T height, Vec2_<T> center)
		:
		tLeft({ center.x - width / 2,center.y - height / 2 }),
		bRight({ center.x + width / 2,center.y + height / 2 })
	{}
	Rect& operator=(const Rect<T>& r)
	{
		this->tLeft = r.tLeft;
		this->bRight = r.bRight;
		return *this;
	}
	T GetWidth()const
	{
		return bRight.x - tLeft.x;
	}
	T GetHeight()const
	{
		return bRight.y - tLeft.y;
	}
	const Vec2_<T>& GetTopLeft()const
	{
		return this->tLeft;
	}
	const Vec2_<T>& GetBotoomRight()const
	{
		return this->bRight;
	}
	bool IsInside(const Vec2_<T>& l)const
	//not working as intend 
	//needs to fix
	{
		if ((l.x > tLeft.x&&l.x < bRight.x) && (l.y > tLeft.y&&l.y < bRight.y))
		{
			return true;
		}
		return false;
	}
	bool IsColliding(const Rect<T>& l)const
	{
		bool sideInside = false;
		bool baseInside = false;
		if (tLeft.x >= l.tLeft.x&&tLeft.x <= l.bRight.x)
			//left side is inside
		{
			sideInside = true;
		}
		if (bRight.x <= l.bRight.x&&bRight.x >= l.tLeft.x)
			//right side is inside
		{
			sideInside = true;
		}
		if (tLeft.y >= l.tLeft.y&&tLeft.y <= l.bRight.y)
			//up side is inside
		{
			baseInside = true;
		}
		if (bRight.y <= l.bRight.y&&bRight.y >= l.tLeft.y)
			//bottom side is inside
		{
			baseInside = true;
		}
		return baseInside && sideInside;
	}
};
typedef Rect<int> RectI;