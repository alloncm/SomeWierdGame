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
	Vec2_<int> RandomVector(int sx, int ex, int sy, int ey);
	Vec2_<int> GetUniqueVector(int sx, int ex, int sy, int ey);
protected:
	Graphics* gfx;
	SimplePlayer* hero;
	int numObs;
	Obs* obs;
	std::vector<Obs*> Obstacles;
	FrameTimer ft; 
	int numObstaclesToGenerate = 10;
	int numEnemiesToGenerate = 5;
	Surface* BackGround;
	std::vector<std::pair<SimpleEnemy*,FrameTimer>*> enemies;
	int numEnemies;
	std::vector<bool> grid;
	std::mt19937 rng;
};