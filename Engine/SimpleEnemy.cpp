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

SimpleEnemy & SimpleEnemy::operator=(const SimpleEnemy & s)
{
	this->backGround = s.backGround;
	this->ball = s.ball;
	this->balls.resize(0);
	this->lives = s.lives;
	this->pos = s.pos;
	this->shootCount = 0.0f;
	this->speed = s.speed;
	this->sprite = s.sprite;
	this->vel = s.vel;
	return *this;
}

SimpleEnemy::SimpleEnemy(const SimpleEnemy & s)
	:
	D2Character(s)
{
	this->lives = s.lives;
	this->ball = s.ball;
	this->shootCount = 0;
	this->balls.resize(0);
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

	float Dtime = ft.Mark();
	for (int i = 0; i < balls.size(); i++)
	{
		bool wreck = false;
		for (int j = 0; j < obs.size(); j++)
		{
			if (this!=obs[j]&&obs[j]->IsColliding(balls[i].get()))
			{
				wreck = true;
				if (typeid(hero) == typeid(obs[j]))
				{
					obs[j]->Hit();
				}
			}
		}
		if (wreck)
		{
			DestroyBall(i);
		}
		else
		{
			balls[i]->Update(Dtime);
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

void SimpleEnemy::Draw(Graphics & gfx)
{
	D2Character::Draw(gfx);
	for (int i = 0; i < balls.size(); i++)
	{
		balls[i]->Draw(gfx);
	}
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
	int i = balls.size() - 1;
	balls[i] = std::make_unique<EnergyBall>(ball);
	balls[i]->SetLocation(this->GetPosition());
	balls[i]->SetDirection(d);
}

void SimpleEnemy::DestroyBall(int i)
{
	balls.erase(balls.begin() + i);
}

void SimpleEnemy::DestroyBalls(const Rect<int>& Border)
{
	for (int i = 0; i < balls.size(); i++)
	{
		if (!balls[i]->GetRect().IsColliding(Border))
		{
			DestroyBall(i);
		}
	}
}
