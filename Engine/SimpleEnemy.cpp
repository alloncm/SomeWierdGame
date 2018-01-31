#include "SimpleEnemy.h"

SimpleEnemy::SimpleEnemy(std::string source, float spe, Vec2 p, int l)
	:
	D2Character(source, spe, p, { 0,0 }, Colors::Magenta),
	lives(l),
	ball(FileNames::blast, spe, { 0,0 }, { 0,0 }),
	balls()
{
	balls.resize(0);
	shootCount = 0;
}

void SimpleEnemy::Update(float dt, Rect<int>border, std::vector<D2Character*> obs,D2Character* hero)
{
	
	SetDirection(hero->GetPosition()-this->pos);
	shootCount += shooter.Mark();
	if (hero->GetRect().IsColliding(this->GetRangeRect()))
	{
		if (shootCount >= shootTime)
		{
			shootCount = 0;
			FireBall(hero->GetPosition() - this->GetPosition());
		}
	}

	//handling the balls

	DestroyBalls(border);

	for (int i = 0; i < balls.size(); i++)
	{
		bool wreck = false;
		for (int j = 0; j < obs.size(); j++)
		{
			if (obs[j]->IsColliding(balls[i].get()))
			{
				wreck = true;
			}
		}
		if (wreck)
		{
			DestroyBall(i);
		}
		else
		{
			balls[i]->Update(ft.Mark());
		}
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

void SimpleEnemy::FireBall(const Vec2 & dir)
{
	Vec2 d = dir;
	d.Normalize();
	balls.resize(balls.size() + 1);
	balls[balls.size() - 1] = std::make_unique<EnergyBall>(ball);
	balls[balls.size() - 1]->SetDirection(dir);
}

void SimpleEnemy::DestroyBall(int i)
{
	balls.erase(balls.begin() + i);
}

void SimpleEnemy::DestroyBalls(const Rect<int>& Border)
{
	for (int i = 0; i < balls.size(); i++)
	{
		if (balls[i]->GetRect().IsColliding(Border))
		{
			DestroyBall(i);
		}
	}
}
