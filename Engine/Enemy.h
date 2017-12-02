#pragma once
#include"DemoCharacter.h"
#include"FileNames.h"
class Enemy : public DemoCharacter
{
public:
	Enemy(float spe, Vec2 p, int w, int h, Vec2_<int> searchStart, int animLong, float ht);
	void Update(float dt , D2Character* dc);
	virtual void SetDirection(const Vec2& dir)override;
private:
	Vec2 MoveEnemy(D2Character* dc);
};