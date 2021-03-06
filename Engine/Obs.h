#pragma once
#include "2DCharacter.h"

//represent an obstacle in the game
class Obs : public D2Character
{
public:
	Obs() = default;
	Obs(std::string source, Vec2 position, Color bg, int width = 0, int height = 0, float speed = 0.0);
	Obs& operator= ( Obs& other)= default;
	Obs(const Obs& other) = default;
	virtual bool Hit()override;
	bool IsColliding(const Rect<int>& re);
	virtual void SetDirection(const Vec2& v)override;
	virtual ~Obs() = default;
};