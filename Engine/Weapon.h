#pragma once
#include"2DCharacter.h"

class Weapon : public D2Character
{
	Weapon(std::string source, float speed, Vec2 position, Vec2 vel, Color bg, int w, int h);

	virtual ~Weapon() = default;
};