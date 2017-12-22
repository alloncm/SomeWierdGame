#pragma once
#include "2DCharacter.h"
class Obs : public D2Character
{
public:
	Obs(std::string source, Vec2 position, Color bg, int width = 0, int height = 0, float speed = 0.0);
	bool IsColliding(D2Character* ch);
	virtual void SetDirection(const Vec2& v)override;
	virtual ~Obs() = default;
};