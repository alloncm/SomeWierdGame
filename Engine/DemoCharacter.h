#pragma once
#include"Animation.h"
#include"2DCharacter.h"

class DemoCharacter : public D2Character
{
public:
	DemoCharacter(std::string s, float spe, Vec2 p, int w, int h, Vec2_<int> searchStart,int animLong,float ht);
	virtual void Draw(Graphics& gfx)override;
	virtual void Update(float dt)override;
	virtual void SetDirection(const Vec2& dir)override;
	const Vec2 GetDirection() const;
protected:
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
protected:
	std::vector<Animation>animations;
	State iCurState;
};
