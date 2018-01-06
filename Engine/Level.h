#pragma once
#include"Player.h"
#include"Obs.h"
#include"Surface.h"
#include"Effects.h"
#include<vector>
#include<random>

//represent a level of the game handles all the connection bewtween the other classes

class Level
{
public:
	Level() = default;
	Level(Player* p,Graphics& gfx,Obs* obs);
	void Draw();									
	void Update(const Vec2& dir, bool Plyerfire);
	virtual ~Level();
	void GenerateObstacles(Obs* obs,int num);
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
	Surface BackGround;
};