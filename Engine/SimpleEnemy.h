#pragma once
#include"2DCharacter.h"
#include <memory>
class SimpleEnemy : public D2Character
{
public:
	SimpleEnemy(std::string source, float spe, Vec2 p, int l = 1);
	SimpleEnemy(const SimpleEnemy& s) = default;
	void Update(float dt, D2Character* dc);
	virtual void SetDirection(const Vec2& dir)override;
	virtual bool Hit()override;
	bool IsAlive();
	virtual ~SimpleEnemy() = default;
private:
	RectI GetRangeRect();
private:
	int lives;
	static constexpr int range = 100;

	//add fire ability
	//the layer walks to the hero if its outside of the range
	//shoots at the pkayer if he is insise the range
};
