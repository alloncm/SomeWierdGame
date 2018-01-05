#include "EnergyBall.h"

EnergyBall::EnergyBall( float speed, Vec2 position,Vec2 dir)
	:
	D2Character(FileNames::blast,speed,position,dir,Colors::Magenta)
{
	vel.x *= speed;
	vel.y *= speed;
}

void EnergyBall::SetDirection(const Vec2 & v)
{
	vel = v*speed;
}

void EnergyBall::Update(float dt)
{
	pos += vel*dt;
}

