#include "Level.h"

Level::Level(Player* p,Graphics& g,Obs* o,Enemy* e)
	:
	gfx(&g),
	BackGround("greenBack.bmp")
{
	numObs = 0;
	obs = o;
	GenerateObstacles(obs, numObstaclesToGenerate);
	hero = p;
	
}

void Level::Draw()
{
	gfx->DrawSprite(0, 0, BackGround, SpriteEffects::Copy());
	for (int i = 0; i < numObs; i++)
	{
		Obstacles[i]->Draw(*gfx);
	}
	enemy->Draw(*gfx);
	hero->Draw(*gfx);
}

void Level::Update(const Vec2& dir,bool fire)
{

	float timer = ft.Mark();
	hero->SetDirection(dir);
	Vec2 pos= hero->GetPosition();
	pos += hero->GetUpdatedPosition(timer);
	Rect<int> heroRect(pos.x, pos.y, hero->GetWidth(), hero->GetHeight());

	//list of all the non player objects
	std::vector<D2Character*> allObs;
	for (int i = 0; i < numObs; i++)
	{
		allObs.emplace_back(enemy);
		allObs.push_back(Obstacles[i]);
	}

	//updating the player
	hero->Update(timer, gfx->GetScreenRect(), allObs, NextMoveValid(heroRect));
	
	//firing the energyballs
	if (fire)
	{
		hero->FireBall();
	}

	//enemy
	enemy->Update(eft.Mark(), hero);
}

Level::~Level()
{
	for (int i = 0; i < numObs; i++)
	{
		delete Obstacles[i];
		Obstacles[i] = nullptr;
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

void Level::GenerateEnemies(int num)
{
	std::mt19937::result_type seed = time(0);
	auto randH = std::bind(std::uniform_int_distribution<int>(0, gfx->ScreenHeight - 1), std::mt19937(seed));
	auto randW = std::bind(std::uniform_int_distribution<int>(0, gfx->ScreenWidth - 1), std::mt19937(seed));

	for (int i = 0; i < num; i++)
	{

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
