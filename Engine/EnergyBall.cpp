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

void EnergyBall::Update(float dt)
{
	pos += direc*dt;
}

void EnergyBall::SetDirection(const Vec2 & v)
{
	direc = v*speed;
}

int EnergyBall::GetWidth()
{
	return sprite.GetWidth();
}

int EnergyBall::GetHeight()
{
	return sprite.GetHeight();
}

const Rect<int> EnergyBall::GetRect() const
{
	return{ {(int)pos.x,(int)pos.y},{(int)pos.x + sprite.GetWidth(),(int)pos.y + sprite.GetHeight() } };
}

void EnergyBall::SetLocation(const Vec2 & p)
{
	pos.x = p.x;
	pos.y = p.y;
}
