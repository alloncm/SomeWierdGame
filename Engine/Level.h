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

//add the sprite manager to the background



//represent a level of the game handles all the connection bewtween the other classes

class Level
{
public:
	Level(SimplePlayer* p,Graphics& gfx,Obs* obs,SimpleEnemy& info);
	void Draw();									
	void Update(const Vec2& dir, Vec2 dirFire);
	virtual ~Level();
	void GenerateObstacles(Obs* obs,int num);
	void GenerateEnemies(SimpleEnemy& info,int num);
	void DeleteDeadEnemies();
	bool IsGameOver();
private:
	bool NextMoveValid( Rect<int> hero);
	Vec2_<int> RandomVector(int sx, int ex, int sy, int ey);			//for random dropping Obj
	Vec2_<int> GetUniqueVector(int sx, int ex, int sy, int ey);			//for random dropping Obj
	std::vector<Vec2> GenerateFromFile( std::string filename);			//for loading from txt file
protected:
	Graphics* gfx;
	SimplePlayer* hero;
	Obs* obs;
	std::vector<Obs*> Obstacles;
	FrameTimer ft; 
	int numObstaclesToGenerate = 10;
	int numEnemiesToGenerate = 5;
	Surface* BackGround;
	std::vector<std::pair<SimpleEnemy*,FrameTimer>*> enemies;
	std::vector<bool> grid;
	std::mt19937 rng;
};