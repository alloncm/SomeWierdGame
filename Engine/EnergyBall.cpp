#include "EnergyBall.h"

EnergyBall::EnergyBall(std::string source, float speed, Vec2 position,Vec2 dir)
	:
	D2Character(source,speed,position,dir,Colors::Magenta)
{
	vel.x *= speed;
	vel.y *= speed;
}


bool EnergyBall::Hit()
{
	return true;
}

void EnergyBall::SetDirection(const Vec2 & v)
{
	vel = v*speed;
}

void EnergyBall::Update(float dt)
{
	pos += vel*dt;
}

