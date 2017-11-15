#include "EnergyBall.h"

EnergyBall::EnergyBall(std::string source, float speed, Vec2 position,Vec2 dir)
	:
	sprite(source),
	speed(speed),
	pos(position),
	direc(dir),
	vel({0.0,0.0})
{
	direc.x *= speed;
	direc.y *= speed;
}

void EnergyBall::Draw(Graphics & gfx)
{
	gfx.DrawSprite((int)pos.x, (int)pos.y, sprite,SpriteEffects::Chroma(Colors::Magenta));
}

void EnergyBall::Update()
{
	pos += direc;
}

void EnergyBall::SetDirection(const Vec2 & v)
{
	direc = v;
}

int EnergyBall::GetWidth()
{
	return sprite.GetWidth();
}

int EnergyBall::GetHeight()
{
	return sprite.GetHeight();
}
