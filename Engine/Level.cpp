#include "Level.h"

Level::Level(SimplePlayer* p,Graphics& g,Obs* o,SimpleEnemy& e)
	:
	gfx(&g)
{
	grid.resize((gfx->ScreenHeight / o->GetHeight())*(gfx->ScreenWidth / o->GetWidth()));
	std::fill(grid.begin(), grid.end(), false);
	numObs = 0;
	numEnemies = 0;
	BackGround = SpriteManager::GetManager().Get(FileNames::back);
	obs = o;
	GenerateObstacles(obs, numObstaclesToGenerate);
	hero = p;
	Vec2_<int> pos = GetUniqueVector(0, gfx->ScreenWidth / obs->GetWidth() - 1, 0, gfx->ScreenHeight / obs->GetHeight() - 1);
	hero->SetLocation(Vec2(pos.x,pos.y));
	GenerateEnemies(e, numEnemiesToGenerate);
}

void Level::Draw()
{
	if (hero->IsAlive())
	{
		//gfx->DrawSprite(0, 0, *BackGround, SpriteEffects::Copy());
		for (int i = 0; i < numObs; i++)
		{
			Obstacles[i]->Draw(*gfx);
		}

		for (int i = 0; i < numEnemies; i++)
		{
			enemies[i]->first->Draw(*gfx);
		}

		hero->Draw(*gfx);
	}
	else
	{
		gfx->DrawSprite(250, 150, *(SpriteManager::GetManager().Get(FileNames::GameOver)),SpriteEffects::Copy());
	}
}

void Level::Update(const Vec2& dir,Vec2 dirFire)
{
	if (hero->IsAlive())
	{
		float timer = ft.Mark();
		hero->SetDirection(dir);
		Vec2 pos = hero->GetPosition();
		pos += hero->GetUpdatedPosition(timer);
		Rect<int> heroRect(int(pos.x), int(pos.y), hero->GetWidth(), hero->GetHeight());

		//list of all the objects
		std::vector<D2Character*> allObs;
		for (int i = 0; i < numObs; i++)
		{
			allObs.push_back(Obstacles[i]);
		}

		for (int i = 0; i < numEnemies; i++)
		{
			allObs.push_back(enemies[i]->first);
		}
		allObs.push_back(hero);

		//updating the player
		hero->Update(timer, gfx->GetScreenRect(), allObs, NextMoveValid(heroRect));
		hero->FireBall(dirFire);

		//enemy

		for (int i = 0; i < numEnemies; i++)
		{
			enemies[i]->first->Update(enemies[i]->second.Mark(), gfx->GetScreenRect(), allObs, hero);

		}


		//delete the dead bodies OF MY ENEMIES
		DeleteDeadEnemies();
	}
}

Level::~Level()
{
	for (int i = 0; i < numObs; i++)
	{
		delete Obstacles[i];
		Obstacles[i] = nullptr;
	}
	
	for (int i = 0; i < numEnemies; i++)
	{
		delete enemies[i]->first;
		enemies[i]->first = nullptr;
		delete enemies[i];
		enemies[i] = nullptr;
	}
	
}

void Level::GenerateObstacles(Obs * obs, int num)
{
	int gridW = gfx->ScreenWidth / obs->GetWidth() -1;
	int gridH = gfx->ScreenHeight / obs->GetHeight()-1 ;
	
	for (int i = 0; i < num; i++)
	{
		Vec2_<int> pos = GetUniqueVector(0, gridW, 0, gridH);
		Obs* ob = new Obs(*obs);
		ob->SetLocation(Vec2(pos.x*ob->GetWidth(),pos.y*ob->GetHeight()));
		Obstacles.emplace_back(ob);
	}
	numObs = num;
	
}
void Level::GenerateEnemies(SimpleEnemy & info, int num)
{
	int gridW = gfx->ScreenWidth / obs->GetWidth()-1;
	int gridH = gfx->ScreenHeight / obs->GetHeight()-1;

	for (int i = 0; i < num; i++)
	{
		Vec2_<int> pos = GetUniqueVector(0, gridW, 0, gridH);
		SimpleEnemy* en = new SimpleEnemy(info);
		en->SetLocation(Vec2(pos.x*en->GetWidth(),pos.y*en->GetHeight()));
		std::pair<SimpleEnemy*, FrameTimer>* pair = new std::pair<SimpleEnemy*, FrameTimer>(en, FrameTimer());
		enemies.emplace_back(pair);
	}
	numEnemies = num;
}
void Level::DeleteDeadEnemies()
{
	for (int i = 0; i < numEnemies; i++)
	{
		if (!enemies[i]->first->IsAlive())
		{
			delete enemies[i]->first;
			enemies[i]->first = nullptr;
			delete enemies[i];
			enemies[i] = nullptr;
			enemies[i] = enemies[numEnemies - 1];
			enemies[numEnemies - 1] = nullptr;
			numEnemies--;
			enemies.shrink_to_fit();
		}
	}
}

bool Level::IsGameOver()
{
	return !hero->IsAlive();
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

Vec2_<int> Level::RandomVector(int sx, int ex, int sy , int ey)
{
	std::uniform_int_distribution<int> xDist(sx, ex);
	std::uniform_int_distribution<int> yDist(sy, ey);
	auto v = Vec2_<int>(xDist(rng), yDist(rng));;
	return v;
}

Vec2_<int> Level::GetUniqueVector(int sx, int ex, int sy, int ey)
{
	int gridW = gfx->ScreenWidth / obs->GetWidth() - 1;
	int gridH = gfx->ScreenHeight / obs->GetHeight() - 1;

	Vec2_<int> pos = RandomVector(sx, ex, sy, ey);
	while (grid[gridW*pos.y + pos.x] == true)
	{
		pos = RandomVector(0, gridW, 0, gridH);
	}
	grid[gridW*pos.y + pos.x] = true;
	return pos;
}
