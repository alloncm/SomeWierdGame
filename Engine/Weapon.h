#pragma once
#include"2DCharacter.h"

//weapon class not in use yet
//all the differenet weapons would inherite from here
class Weapon : public D2Character
{
	Weapon(std::string source, float speed, Vec2 position, Vec2 vel, Color bg, int w, int h);

	virtual ~Weapon() = default;
};