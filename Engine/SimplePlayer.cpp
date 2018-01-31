#include "SimplePlayer.h"
//need to add string for sprite
SimplePlayer::SimplePlayer(float spe, Vec2 p,EnergyBall & b)
	:
	D2Character(FileNames::SHero , spe, p, vel, Colors::Magenta),
	live(lives),
	countB(0)
{
	ball = b;
	balls = new EnergyBall*[countB];
}

void SimplePlayer::SetDirection(const Vec2 & dir)
{
	Vec2 d = dir;
	d.Normalize();
	vel = d*speed;
}

bool SimplePlayer::Hit()
{
	live--;
	return live == 0;
}

void SimplePlayer::FireBall(Vec2& dir)
{
	ball.SetDirection(dir);
	ball.SetLocation(GetBallMatchingPosition());
	if (dir.GetLength() != 0)
	{
		CreateBall();
	}
}

void SimplePlayer::Draw(Graphics & gfx)
{
	D2Character::Draw(gfx);
	for (int i = 0; i < countB; i++)
	{
		balls[i]->Draw(gfx);
	}
}

bool SimplePlayer::IsAlive()
{
	return live != 0;
}

void SimplePlayer::Update(float dt, Rect<int> border, std::vector<D2Character*> obs, bool canMove)
{
	Vec2 last = this->pos;
	D2Character::Update(dt);
	if (!canMove)
	{
		this->pos = last;
	}
	DestroyFireBall(border);

	while (!obs.empty())
	{
		//destroy any ball that touches other objects
		D2Character* ob = obs.back();
		for (int i = 0; i < countB; i++)
		{
			if (ob->IsColliding(balls[i]))
			{
				DestroyBall(i);
			}
		}
		obs.pop_back();
	}
	//Updates the balls
	float bdt = ft.Mark();
	for (int i = 0; i < countB; i++)
	{
		balls[i]->Update(bdt);
	}
}

SimplePlayer::~SimplePlayer()
{
	for (int i = 0; i < countB; i++)
	{
		delete balls[i];
		balls[i] = nullptr;
	}
	delete[] balls;
}

Vec2 SimplePlayer::GetBallMatchingPosition()
{
	return this->pos + Vec2((sprite->GetWidth()/ 2) - (ball.GetWidth()/2), (sprite->GetHeight() / 2) - (ball.GetHeight()/2));
}

void SimplePlayer::DestroyFireBall(Rect<int> Border)
{
	for (int i = 0; i < countB; i++)
	{
		if (balls[i] != nullptr)
		{
			bool col = balls[i]->GetRect().IsColliding(Border);		//checks if the ball is in bounds 
			if (!col)
			{
				DestroyBall(i);
			}
		}
	}
}

void SimplePlayer::DestroyBall(int i)
{
	//delete the ball
	delete balls[i];
	balls[i] = nullptr;
	balls[i] = balls[countB - 1];			//move the deleted 
	countB--;
}

void SimplePlayer::CreateBall()
{
	if (countB == 0)		//the first ball
	{
		balls = new EnergyBall*[countB + 1];
		balls[countB] = new EnergyBall;
		*balls[countB] = ball;
		countB++;
	}
	else
	{
		int j = 0;								//counts the number of elements in balls
		EnergyBall** temp = new EnergyBall*[countB + 1];		//temporary place to copy only the valid elemets 
		for (int i = 0; i < countB; i++)
		{
			if (balls[i] != nullptr)		//copies only if not nullptr
			{
				temp[j] = balls[i];
				balls[i] = nullptr;
				j++;						//keep track of how many copied
			}
		}
		delete[] balls;
		balls = new EnergyBall*[j + 1];		//realocate the memory 
		for (int i = 0; i < j; i++)			//copies the loctions of the values to the new alocated memory
		{
			balls[i] = temp[i];
			temp[i] = nullptr;
		}
		delete[] temp;
		temp = nullptr;
		countB = j;
		balls[countB] = new EnergyBall;			//alocate memory for another element
		*balls[countB] = ball;
		countB++;
	}
}


