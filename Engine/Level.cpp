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
	hero->Update(timer, gfx->GetScreenRect());
	hero->SetDirection(dir);
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
