#pragma once
#include"Player.h"
#include"Obs.h"
#include"Surface.h"
#include"Effects.h"
#include<vector>
#include<random>
#include<functional>
#include<algorithm>
#include<utility>
#include<fstream>
#include"SimpleEnemy.h"
#include"SpritesManager.h"
#include"SimplePlayer.h"
#include"LevelCon.h"

//add the sprite manager to the background



//represent a level of the game handles all the connection bewtween the other classes

class Level
{
public:
	Level(SimplePlayer* p,Graphics& gfx,Obs* obs,SimpleEnemy& info);
	void Draw();									
	void Update(const Vec2& dir, Vec2 dirFire);
	virtual ~Level();
	void GenerateObstacles(Obs* obs);
	void GenerateEnemies(SimpleEnemy& info);
	bool SwitchNextLevel();
	void DeleteDeadEnemies();
	bool IsGameOver();
private:
	bool NextMoveValid( Rect<int> hero);
	Vec2_<int> RandomVector(int sx, int ex, int sy, int ey);			//for random dropping Obj //not using right now
	Vec2_<int> GetUniqueVector(int sx, int ex, int sy, int ey);			//for random dropping Obj //not using right now
	std::vector<Vec2> GenerateFromFile( std::string filename);			//for loading from txt file //not using right now
protected:
	Graphics* gfx;
	SimplePlayer* hero;
	Obs* obs;
	SimpleEnemy* ene;
	std::vector<Obs*> Obstacles;
	FrameTimer ft; 
	std::vector<std::pair<SimpleEnemy*,FrameTimer>*> enemies;
	std::vector<bool> grid;
	std::mt19937 rng;
	std::vector<LevelCon>Levels;
	int level;
};