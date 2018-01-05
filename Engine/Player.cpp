#include "Player.h"

Player::Player(float spe, Vec2 p, int w, int h, Vec2_<int> searchStart, int animLong, float ht,EnergyBall& b)
	:
	DemoCharacter(FileNames::hero, spe, p, w, h, searchStart, animLong, ht,lives)
{
	ball = b;
	countB = 0;
	balls = nullptr;
}


void Player::FireBall()
{
	Vec2 v = GetDirection();		//sets the position of the ball to match the character

	ball.SetLocation(GetBallMatchingPosition());
	//updates the directoio of the ball based on the velocity of the caracter
	if (v.x > 1)
	{
		v.x = 1;
	}
	if (v.y > 1)
	{
		v.y = 1;
	}
	if (v.x < -1)
	{
		v.x = -1;
	}
	if (v.y < -1)
	{
		v.y = -1;
	}
	ball.SetDirection(v);
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

void Player::DestroyFireBall(Rect<int>border)
{
	for (int i = 0; i < countB; i++)
	{
		if (balls[i] != nullptr)
		{
			bool col = balls[i]->GetRect().IsColliding(border);		//checks if the ball is in bounds 
			if (!col)
			{
				//delete the ball
				delete balls[i];
				balls[i] = nullptr;
				balls[i] = balls[countB - 1];			//move the deleted 
				countB--;
			}
		}
 	}
}

void Player::Update(float dt, Rect<int> border, std::vector<D2Character*> obs)
{
	DemoCharacter::Update(dt);
	DestroyFireBall(border);
	while (!obs.empty())
	{
		D2Character* ob = obs.back();
		for (int i = 0; i < countB; i++)
		{
			if (ob->IsColliding(balls[i]))
			{
				delete balls[i];
				balls[i] = balls[countB - 1];
				balls[countB - 1] = nullptr;
				countB--;
			}
		}
		obs.pop_back();
	}
	float bdt = ft.Mark();
	for (int i = 0; i < countB; i++)
	{
		balls[i]->Update(bdt);
	}
}

void Player::Draw(Graphics & gfx)
{
	DemoCharacter::Draw(gfx);
	for (int i = 0; i < countB; i++)
	{
		balls[i]->Draw(gfx);
	}
}

Player::~Player()
{
	for (int i = 0; i < countB; i++)
	{
		delete balls[i];
	}
	delete balls;
}

Vec2 Player::GetBallMatchingPosition()
{
	Vec2 vtr = GetPosition();

	Vec2 v = GetDirection();
	//make sure v values are 1 or 0
	if (v.x > 0 && v.x < 1)
	{
		v.x = 1;
	}
	else if (v.x < 0 && v.x > -1)
	{
		v.x = -1;
	}
	if (v.y > 0 && v.y < 1)
	{
		v.y = 1;
	}
	else if (v.y < 0 && v.y > -1)
	{
		v.y = -1;
	}
	Vec2_<int> p((int)v.x, (int)v.y);
	if (p.x == 1)	//looking right
	{
		vtr.x += GetWidth();
	}
	if (p.x == -1)	//looking left
	{
		vtr.x -= ball.GetWidth();
	}
	if (p.x == 0 && p.y == -1)	//looking up
	{
		vtr.x += ((GetWidth() / 2) - (ball.GetWidth() / 2));
		vtr.y -= ball.GetHeight();
	}
	if (p.x == 0 && p.y == 1)	//looking down
	{
		vtr.x += ((GetWidth() / 2) - (ball.GetWidth() / 2));
		vtr.y += GetHeight();
	}

	return vtr;
}
