#include "Level.h"

Level::Level(Player* p,Graphics& g,Obs* o)
	:
	gfx(&g)      
{
	numObs = 0;
	obs = o;
	Obstacles.insert(Obstacles.begin(), new Obs);
	*Obstacles[numObs] = *obs;
	numObs++;
	hero = p;
}

void Level::Draw()
{
	for (int i = 0; i < numObs; i++)
	{
		Obstacles[i]->Draw(*gfx);
	}
	hero->Draw(*gfx);
}

void Level::Update(const Vec2& dir,bool fire)
{
	float timer = ft.Mark();
	//problem with the copy constructor of Player needs to check again about copy constructor and assigment cause im a dumb shit
	if (NextMoveValid(dir, *hero, timer))
	{
		hero->Update(timer, gfx->GetScreenRect());
		hero->SetDirection(dir);
	}
	if (fire)
	{
		hero->FireBall();
	}
}

Level::~Level()
{
	for (int i = 0; i < numObs; i++)
	{
		delete Obstacles[i];
		Obstacles[i] = nullptr;
	}
}

bool Level::NextMoveValid(const Vec2 & dir, Player copy,float mark)
{
	copy.Update(mark, gfx->GetScreenRect());
	copy.SetDirection(dir);
	bool valid = true;
	for (int i = 0; i < numObs; i++)
	{
		if (Obstacles[i]->IsColliding(&copy))
		{
			valid = false;
		}
	}
	return valid;
}
