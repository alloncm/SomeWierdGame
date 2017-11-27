#pragma once
#include"DemoCharacter.h"

class Enemy : public DemoCharacter
{
public:
	Enemy(std::string s, float spe, Vec2 p, int w, int h, Vec2_<int> searchStart, int animLong, float ht);
	
	void MoveEnemy(DemoCharacter& dc);
};