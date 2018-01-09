#pragma once
#include"Player.h"
#include"Obs.h"
#include"Surface.h"
#include"Effects.h"
#include<vector>
#include<random>
#include<functional>
#include<utility>
#include"Enemy.h"


//an object to hold the info to create the enemy;
struct EnemyInfo
{
private:
	float speed;
	int width;
	int height;
	Vec2_<int> searchStart;
	int animLong;
	float holdtime;
	int lives = 1;

public:
	EnemyInfo(float spe, int w, int h, Vec2_<int> search, int anLong, float ht, int live = 1)
		:
		speed(spe),
		width(w),
		height(h),
		searchStart(search),
		animLong(anLong),
		holdtime(ht),
		lives(live)
	{
	}

	Enemy* Generate(Vec2_<float> pos)
	{
		return new Enemy(speed, pos, width, height, searchStart, animLong, holdtime);
	}
};

//represent a level of the game handles all the connection bewtween the other classes

class Level
{
public:
	Level() = default;
	Level(Player* p,Graphics& gfx,Obs* obs,EnemyInfo& info);
	void Draw();									
	void Update(const Vec2& dir, bool Plyerfire);
	virtual ~Level();
	void GenerateObstacles(Obs* obs,int num);
	void GenerateEnemies(EnemyInfo& info,int num);
private:
	bool NextMoveValid( Rect<int> hero);
protected:
	Graphics* gfx;
	Player* hero;
	int numObs;
	Obs* obs;
	std::vector<Obs*> Obstacles;
	FrameTimer ft; 
	int numObstaclesToGenerate = 10;
	int numEnemiesToGenerate = 5;
	Surface BackGround;
	std::vector<std::pair<Enemy*,FrameTimer>> enemies;
	int numEnemies;
};