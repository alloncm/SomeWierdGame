#pragma once
#include"Player.h"
#include"Obs.h"
#include"Surface.h"
#include"Effects.h"
#include<vector>
#include<random>
#include<functional>
#include<utility>
#include"SimpleEnemy.h"
#include"SpritesManager.h"
#include"SimplePlayer.h"

//add the sprite manager to the background

//an object to hold the info to create the enemy;
struct EnemyInfo
{
private:
	float speed;
	int width;
	int height;
	int lives = 3;

public:
	EnemyInfo(float spe, int w, int h, int live = 1)
		:
		speed(spe),
		width(w),
		height(h),
		lives(live)
	{
	}

	SimpleEnemy* Generate(Vec2_<float> pos)
	{
		return new SimpleEnemy(FileNames::SEnemy,speed, pos, width, height,lives);
	}
};

//represent a level of the game handles all the connection bewtween the other classes

class Level
{
public:
	Level() = default;
	Level(SimplePlayer* p,Graphics& gfx,Obs* obs,EnemyInfo& info);
	void Draw();									
	void Update(const Vec2& dir, Vec2 dirFire);
	virtual ~Level();
	void GenerateObstacles(Obs* obs,int num);
	void GenerateEnemies(EnemyInfo& info,int num);
	void DeleteDeadEnemies();
	bool IsGameOver();
private:
	bool NextMoveValid( Rect<int> hero);
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
};