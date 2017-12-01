#pragma once
#include"DemoCharacter.h"
#include"FileNames.h"
class Enemy : public DemoCharacter
{
public:
	Enemy(float spe, Vec2 p, int w, int h, Vec2_<int> searchStart, int animLong, float ht);
	void Update(float dt , D2Character* dc);
private:
	Vec2 MoveEnemy(D2Character* dc);
};