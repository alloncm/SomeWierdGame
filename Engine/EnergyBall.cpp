#include "EnergyBall.h"

EnergyBall::EnergyBall( float speed, Vec2 position,Vec2 dir)
	:
	D2Character(FileNames::blast,speed,position,{0,0},Colors::Magenta),
	direc(dir)
{
	direc.x *= speed;
	direc.y *= speed;
}

void EnergyBall::SetDirection(const Vec2 & v)
{
	direc = v*speed;
}

void EnergyBall::Update(float dt)
{
	pos += direc*dt;
}


