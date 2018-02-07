#include "LevelCon.h"

LevelCon::LevelCon(std::string hero, std::string obs, std::string ene)
	:
	Hero(GenerateFromFile(hero)[0]),
	Obstacles(GenerateFromFile(obs)),
	Enemies(GenerateFromFile(ene))
{
}

std::vector<Vec2> LevelCon::GenerateFromFile(std::string filename)
{
	std::vector<Vec2>v;
	std::ifstream fin(filename);
	fin.exceptions(std::ios::badbit);
	while (fin.peek() != EOF)
	{
		char c = fin.get();
		Vec2 pos;
		//getting the pos for the new obs
		if (c == '(')
		{
			c = fin.get();
			std::string buffer = "";
			while (c != ',')
			{

				buffer += c;
				c = fin.get();
			}
			try
			{
				pos.x = std::stoi(buffer);
			}
			catch (...)
			{
				std::string s = "unable to load the place of the Obstacles from file: " + filename;
				throw std::exception(s.c_str());
			}
			c = fin.get();
			buffer = "";
			while (c != ')')
			{
				buffer += c;
				c = fin.get();
			}
			try
			{
				pos.y = std::stoi(buffer);
			}
			catch (...)
			{
				std::string s = "unable to load the place of the Obstacles from file: " + filename;
				throw std::exception(s.c_str());
			}
		}
		c = fin.get();
		v.emplace_back(pos);
	}
	return v;
}

const std::vector<Vec2>& LevelCon::GetObs() const
{
	return Obstacles;
}

const std::vector<Vec2>& LevelCon::GetEne() const
{
	return Enemies;
}

const Vec2 & LevelCon::GetHero() const
{
	return Hero;
}

