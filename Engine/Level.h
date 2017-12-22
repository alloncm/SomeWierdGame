#pragma once
#include"Player.h"
#include"Obs.h"
#include"Surface.h"
#include<vector>

class Level
{
public:
	
protected:
	Player hero;
	std::vector<Obs> Obstacles;
	Surface backGround;
};