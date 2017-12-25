#pragma once
#include"Player.h"
#include"Obs.h"
#include"Surface.h"
#include"Effects.h"
#include<vector>

class Level
{
public:
	Level() = default;
	Level(Player* p,Graphics& gfx);
	//Level(Player p, std::vector<Obs> o, Surface background);
	void Draw();
	void Update(const Vec2& dir, bool fire);
protected:
	Graphics* gfx;
	Player* hero;
	//std::vector<Obs> Obstacles;
	FrameTimer ft; 
};