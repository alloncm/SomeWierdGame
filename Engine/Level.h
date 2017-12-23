#pragma once
#include"Player.h"
#include"Obs.h"
#include"Surface.h"
#include<vector>

class Level
{
public:
	Level() = default;
	Level(std::string bg,Player* p);
	//Level(Player p, std::vector<Obs> o, Surface background);
	void Draw(Graphics& gfx);
protected:
	Player* hero;
	//std::vector<Obs> Obstacles;
	Surface backGround;
};