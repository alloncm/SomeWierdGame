#pragma once
#include"DemoCharacter.h"
#include"FileNames.h"
#include<cmath>

//a class to hold an enemy
class Enemy : public DemoCharacter
{
public:
	Enemy(float spe, Vec2 p, int w, int h, Vec2_<int> searchStart, int animLong, float ht,int live = 1);
	Enemy(const Enemy&) = default;
	void Update(float dt , D2Character* dc);
	virtual void SetDirection(const Vec2& dir)override;
	virtual ~Enemy() = default;
private:
	Vec2 MoveEnemy(D2Character* dc);
};