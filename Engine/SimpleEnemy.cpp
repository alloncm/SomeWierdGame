#include "SimpleEnemy.h"

SimpleEnemy::SimpleEnemy(std::string source, float spe, Vec2 p,  int l)
	:
	D2Character(source,spe,p,{0,0},Colors::Magenta),
	lives(l)
{
}

void SimpleEnemy::Update(float dt, D2Character * hero)
{
	SetDirection(hero->GetPosition()-this->pos);
	if (hero->GetRect().IsColliding(this->GetRangeRect()))
	{
		//fire at the hero
	}
	else
	{
		D2Character::Update(dt);
	}
}

void SimpleEnemy::SetDirection(const Vec2 & dir)
{
	Vec2 d = dir;
	d.Normalize();
	vel = d*speed;
}

bool SimpleEnemy::Hit()
{
	lives--;
	return lives == 0;
}

bool SimpleEnemy::IsAlive()
{
	return lives != 0;
}

RectI SimpleEnemy::GetRangeRect()
{
	return RectI({ int(pos.x) - range,int(pos.y) - range }, { int(pos.x) +sprite->GetWidth()+ range,int(pos.y) + sprite->GetHeight() + range });
}
