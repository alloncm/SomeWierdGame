#pragma once
#include"Animation.h"
#include"2DCharacter.h"

class DemoCharacter : public D2Character
{
public:
	DemoCharacter(std::string s, float spe, Vec2 p, int w, int h, Vec2_<int> searchStart,int animLong,float ht);
	virtual void Draw(Graphics& gfx);
	virtual void Update(float dt);
	virtual void SetDirection(const Vec2& dir);
	const Vec2 GetDirection() const;
private:
	enum class State
	{
		WalkDown,
		StandDown,
		WalkLeft,
		StandLeft,
		WalkRight,
		StandRight,
		WalkUp,
		StandUp,
		Count
	};
private:
	std::vector<Animation>animations;
	State iCurState;
};
