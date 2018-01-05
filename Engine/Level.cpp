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
	hero->SetDirection(dir);
	Vec2 pos= hero->GetPosition();
	pos += hero->GetUpdatedPosition(timer);
	Rect<int> heroRect(pos.x, pos.y, hero->GetWidth(), hero->GetHeight());
	if (NextMoveValid(heroRect))
	{
		std::vector<D2Character*> allObs;
		allObs.push_back(Obstacles[0]);
		hero->Update(timer, gfx->GetScreenRect(),allObs);
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

bool Level::NextMoveValid(Rect<int> hero)
{
	bool valid = true;
	for (int i = 0; i < numObs; i++)
	{
		if (Obstacles[i]->IsColliding(hero))
		{
			valid = false;
		}
	}
	return valid;
}
