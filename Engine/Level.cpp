#include "Level.h"

Level::Level(SimplePlayer* p,Graphics& g,Obs* o,SimpleEnemy& e)
	:
	gfx(&g)
{
	grid.resize((gfx->ScreenHeight / o->GetHeight())*(gfx->ScreenWidth / o->GetWidth()));
	std::fill(grid.begin(), grid.end(), false);
	BackGround = SpriteManager::GetManager().Get(FileNames::back);
	obs = o;
	GenerateObstacles(obs, numObstaclesToGenerate);
	hero = p;
	GenerateEnemies(e, numEnemiesToGenerate);
}

void Level::Draw()
{
	if (hero->IsAlive())
	{
		//gfx->DrawSprite(0, 0, *BackGround, SpriteEffects::Copy());
		for (int i = 0; i < Obstacles.size(); i++)
		{
			Obstacles[i]->Draw(*gfx);
		}

		for (int i = 0; i <enemies.size(); i++)
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
		for (int i = 0; i <Obstacles.size(); i++)
		{
			allObs.push_back(Obstacles[i]);
		}

		for (int i = 0; i < enemies.size(); i++)
		{
			allObs.push_back(enemies[i]->first);
		}
		allObs.push_back(hero);

		//updating the player
		hero->Update(timer, gfx->GetScreenRect(), allObs, NextMoveValid(heroRect));
		hero->FireBall(dirFire);

		//enemy

		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->first->Update(enemies[i]->second.Mark(), gfx->GetScreenRect(), allObs, hero);

		}


		//delete the dead bodies OF MY ENEMIES
		DeleteDeadEnemies();
	}
}

Level::~Level()
{
	for (int i = 0; i < Obstacles.size(); i++)
	{
		delete Obstacles[i];
		Obstacles[i] = nullptr;
	}
	
	for (int i = 0; i < enemies.size(); i++)
	{
		delete enemies[i]->first;
		enemies[i]->first = nullptr;
		delete enemies[i];
		enemies[i] = nullptr;
	}
	
}

void Level::GenerateObstacles(Obs * obs, int num)
{
	std::string filename = "Level0Obs.txt";
	auto v = GenerateFromFile(filename);
	for(int i=0;i<v.size();i++)
	{
		//create the Obstacle
		Obs* ob = new Obs(*obs);
		ob->SetLocation(v[i]);
		Obstacles.emplace_back(ob);
	}
}
void Level::GenerateEnemies(SimpleEnemy & info, int num)
{
	std::string filename = "Level0Ene.txt";
	auto v = GenerateFromFile(filename);
	for(int i=0;i<v.size();i++)
	{
		SimpleEnemy* en = new SimpleEnemy(info);
		en->SetLocation(v[i]);
		std::pair<SimpleEnemy*, FrameTimer>* pair = new std::pair<SimpleEnemy*, FrameTimer>(en, FrameTimer());
		enemies.emplace_back(pair);
	}
}
void Level::DeleteDeadEnemies()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (!enemies[i]->first->IsAlive())
		{
			delete enemies[i]->first;
			enemies[i]->first = nullptr;
			delete enemies[i];
			enemies[i] = nullptr;
			enemies[i] = enemies[enemies.size() - 1];
			enemies[enemies.size() - 1] = nullptr;
			enemies.resize(enemies.size() - 1);
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
	for (int i = 0; i < Obstacles.size(); i++)
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

std::vector<Vec2> Level::GenerateFromFile(std::string filename)
{
	std::vector<Vec2>v;
	std::ifstream fin(filename);
	fin.exceptions(std::ios::badbit);
	while (fin.peek() != EOF)
	{
		char c = fin.get();
		Vec2 pos;
		//getting the pos for the new obs
		if (c == '(')
		{
			c = fin.get();
			std::string buffer = "";
			while (c != ',')
			{

				buffer += c;
				c = fin.get();
			}
			try
			{
				pos.x = std::stoi(buffer);
			}
			catch (...)
			{
				throw std::exception("unable to load the place of the Obstacles");
			}
			c = fin.get();
			buffer = "";
			while (c != ')')
			{
				buffer += c;
				c = fin.get();
			}
			try
			{
				pos.y = std::stoi(buffer);
			}
			catch (...)
			{
				throw std::exception("unable to load the place of the Obstacles");
			}
		}
		c = fin.get();
		v.emplace_back(pos);
	}
	return v;
}
