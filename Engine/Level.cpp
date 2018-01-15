#include "Level.h"

Level::Level(Player* p,Graphics& g,Obs* o,EnemyInfo& e)
	:
	gfx(&g),
	BackGround("greenBack.bmp")
{
	numObs = 0;
	numEnemies = 0;
	obs = o;
	GenerateObstacles(obs, numObstaclesToGenerate);
	hero = p;
	GenerateEnemies(e, numEnemiesToGenerate);
}

void Level::Draw()
{
	gfx->DrawSprite(0, 0, BackGround, SpriteEffects::Copy());
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

void Level::Update(const Vec2& dir,bool fire)
{
	float timer = ft.Mark();
	hero->SetDirection(dir);
	Vec2 pos= hero->GetPosition();
	pos += hero->GetUpdatedPosition(timer);
	Rect<int> heroRect(int(pos.x), int(pos.y), hero->GetWidth(), hero->GetHeight());

	//list of all the non player objects
	std::vector<D2Character*> allObs;
	for (int i = 0; i < numObs; i++)
	{
		allObs.push_back(Obstacles[i]);
	}
	for (int i = 0; i < numEnemies; i++)
	{
		allObs.push_back(enemies[i]->first);
	}

	//updating the player
	hero->Update(timer, gfx->GetScreenRect(), allObs, NextMoveValid(heroRect));
	
	//firing the energyballs
	if (fire)
	{
		hero->FireBall();
	}

	//enemy
	for (int i = 0; i < numEnemies; i++)
	{
		enemies[i]->first->Update(enemies[i]->second.Mark(), hero);
		if (enemies[i]->first->IsColliding(hero))
		{
			hero->Hit();
		}
	}

	//delete the dead bodies OF MY ENEMIES
	DeleteDeadEnemies();
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
	std::mt19937::result_type seed = time(0);
	auto randH = std::bind(std::uniform_int_distribution<int>(0, gfx->ScreenHeight - 1), std::mt19937(seed));
	auto randW = std::bind(std::uniform_int_distribution<int>(0, gfx->ScreenWidth - 1), std::mt19937(seed));
	for (int i = 0; i < num; i++)
	{
		Vec2 pos(randW(),randH());
		Obs* ob = new Obs;
		*ob = *obs;
		ob->SetLocation(pos);
		Obstacles.emplace_back(ob);
	}
	numObs = num;
	
}

void Level::GenerateEnemies(EnemyInfo& info, int num)
{
	std::mt19937::result_type seed = time(0);
	auto randH = std::bind(std::uniform_int_distribution<int>(0, gfx->ScreenHeight - 1), std::mt19937(seed));
	auto randW = std::bind(std::uniform_int_distribution<int>(0, gfx->ScreenWidth - 1), std::mt19937(seed));
	
	for (int i = 0; i < num; i++)
	{
		Vec2 pos(randW(), randH());
		Enemy* en = info.Generate(pos);
		std::pair<Enemy*, FrameTimer>* pair = new std::pair<Enemy*, FrameTimer>(en, FrameTimer());
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
