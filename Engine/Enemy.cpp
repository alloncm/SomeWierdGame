#include "Enemy.h"

Enemy::Enemy(float spe, Vec2 p, int w, int h, Vec2_<int> searchStart, int animLong, float ht,int live)
	:
	DemoCharacter(FileNames::enemy,spe,p,w,h,searchStart,animLong,ht,live)
{
}

Vec2 Enemy::MoveEnemy(D2Character* dc)
{
	Vec2 dir(0, 0);
	if (this->pos.Distance(dc->GetPosition()) > dc->GetWidth()/2)
	{
		 dir = dc->GetPosition();
		dir -= this->GetPosition();
		vel = dir.Normalize()*speed;
	}
	return dir;
}

void Enemy::Update(float dt, D2Character* dc)
{
	SetDirection(MoveEnemy(dc));
	DemoCharacter::Update(dt);
}

void Enemy::SetDirection(const Vec2 & dir)
{
	DemoCharacter::SetDirection(dir);
	float x = std::abs(dir.x);
	float y = std::abs(dir.y);
	if (y>x)
	{
		if (dir.y < 0)
		{
			iCurState = State::WalkUp;
		}
		else
		{
			iCurState = State::WalkDown;
		}
	}
	vel = dir*speed;
}

