#include "DemoCharacter.h"

DemoCharacter::DemoCharacter(std::string s, float spe, Vec2 p, int w, int h, Vec2_<int> searchStart,int animLong,float ht,int l)
	:
	D2Character(s,spe,p,{0,0},Colors::Magenta,w,h),
	iCurState(State::StandDown)
{
	for (int i = 0; i < (int)State::Count; i++)
	{
		animations.emplace_back(Animation(searchStart.x+w, searchStart.y+(h*i), w, h, animLong,sprite, ht, backGround));
		animations.emplace_back(Animation(searchStart.x, searchStart.y+(h*i), w, h, 1,sprite, ht, backGround));
	}
	live = l;
}


void DemoCharacter::Draw(Graphics & gfx)
{
	animations[(int)iCurState].Draw({ (int)pos.x, (int)pos.y }, gfx);
}

void DemoCharacter::Update(float dt)
{
	pos += vel*dt;
	animations[(int)iCurState].Update(dt);
}

bool DemoCharacter::Hit()
{
	live--;
	if (live == 0)
	{
		return true;
	}
	return false;
	//add code to handle death
}

bool DemoCharacter::IsAlive()
{
	if (live == 0)
	{
		return false;
	}
	return true;
}

void DemoCharacter::SetDirection(const Vec2 & dir)
{
	Vec2 d = dir;
	d.Normalize();
	vel = d*speed;
		//check this the character wont stop the animation
	if (dir.x < 0)
	{
		iCurState = State::WalkLeft;
	}
	else if (dir.x > 0)
	{
		iCurState = State::WalkRight;
	}
	else if (dir.y > 0)
	{
		iCurState = State::WalkDown;
	}
	else if (dir.y < 0)
	{
		iCurState = State::WalkUp;
	}
	else
	{
		if (vel.x < vel.y)
		{
			if (vel.y > 0)
			{
				iCurState = State::StandDown;
			}
			else if (vel.y < 0)
			{
				iCurState = State::StandUp;
			}
		}
		else if(vel.x>vel.y)
		{
			if (vel.x < 0)
			{
				iCurState = State::StandLeft;
			}
			else if (vel.x > 0)
			{
				iCurState = State::StandRight;
			}
		}
		else
		{
			int state = int(iCurState);
			if ( state%2==0)
			{
				iCurState = static_cast<State>(state+1);
			}
		}
		
		
	}
	
}

const Vec2& DemoCharacter::GetDirection() const
{
	Vec2 dir = { 0.0,0.0 };
	if (vel != dir)
	{
		dir = vel;
		dir.Normalize();
	}
	else if ((int)iCurState == 0 || (int)iCurState == 1)
	{
		dir.y = 1;
	}
	else if ((int)iCurState == 2 || (int)iCurState == 3)
	{
		dir.x = -1;
	}
	else if ((int)iCurState == 4 || (int)iCurState == 5)
	{
		dir.x = 1;
	}
	else if ((int)iCurState == 6 || (int)iCurState == 7)
	{
		dir.y = -1;
	}
	return dir;
}