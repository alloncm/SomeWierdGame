#pragma once
#include "Surface.h"
#include"Graphics.h"
#include "Effects.h"

class EnergyBall
{
private:
	Surface sprite;
	Vec2 pos;
	Vec2 vel;
	float speed;
	Vec2 direc;
public:
	EnergyBall(std::string source,float speed,Vec2 position,Vec2 dir);
	EnergyBall() = default;
	EnergyBall& operator=(EnergyBall& b) = default;
	void Draw(Graphics& gfx);
	void Update();
	void SetDirection(const Vec2& v);
	int GetWidth();
	int GetHeight();
	const Rect<int> GetRect()const;
};