#pragma once
#include "2DCharacter.h"

//represent an obstacle in the game
class Obs : public D2Character
{
public:
	Obs(std::string source, Vec2 position, Color bg, float speed = 0.0);
	Obs& operator= ( Obs& other)= default;
	Obs(const Obs& other) = default;
	virtual bool Hit()override;
	bool IsColliding(const Rect<int>& re);
	virtual void SetDirection(const Vec2& v)override;
	virtual ~Obs() = default;
};