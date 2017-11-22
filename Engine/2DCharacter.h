#pragma once
#include"Surface.h"
#include"Graphics.h"

class D2Character
{
public:
	D2Character() = default;
	D2Character(std::string source, float speed, Vec2 position, Vec2 vel,Color bg);
	D2Character& operator=(D2Character& b) = default;
	virtual void Draw(Graphics& gfx);
	void Update(float dt);
	virtual void SetDirection(const Vec2& v) = 0;
	int GetWidth()const;
	int GetHeight()const;
	const Rect<int> GetRect()const;
	void SetLocation(const Vec2& p);

protected:
	Surface sprite;
	Vec2 pos;
	Vec2 vel;
	float speed;
	Color backGround;
	int width;
	int height;
};