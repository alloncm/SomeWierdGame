#pragma once
#include<string>
#include<vector>
#include<fstream>
#include"Vec2.h"
class LevelCon
{
public:
	LevelCon(std::string hero, std::string obs, std::string ene);
	std::vector<Vec2> GenerateFromFile(std::string filename);
	const std::vector<Vec2>& GetObs()const;
	const std::vector<Vec2>& GetEne()const;
	const Vec2& GetHero()const;
private:
	std::vector<Vec2> Obstacles;
	std::vector<Vec2> Enemies;
	Vec2 Hero;
};