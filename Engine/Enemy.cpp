#include "Enemy.h"

Enemy::Enemy(float spe, Vec2 p, int w, int h, Vec2_<int> searchStart, int animLong, float ht)
	:
	DemoCharacter(FileNames::enemy,spe,p,w,h,searchStart,animLong,ht)
{
}

Vec2 Enemy::MoveEnemy(D2Character* dc)
{
	Vec2 dir = dc->GetPosition();
	dir -= this->GetPosition();
	vel = dir.Normalize()*speed;

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
	//finish this up so the enemy will walk up and down too
	if (dir.y > 0 && dir.y > dir.x)
	{
		iCurState = State::WalkDown;
	}
}

