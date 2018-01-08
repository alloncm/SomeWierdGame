#pragma once
#include"Animation.h"
#include"2DCharacter.h"

class DemoCharacter : public D2Character
{
public:
	DemoCharacter(std::string s, float spe, Vec2 p, int w, int h, Vec2_<int> searchStart, int animLong, float ht, int live = 1);
	DemoCharacter(const DemoCharacter& other) = default;
	virtual void Draw(Graphics& gfx)override;
	virtual void Update(float dt)override;
	virtual void Hit()override;
	virtual void SetDirection(const Vec2& dir)override;
	const Vec2& GetDirection() const;
	virtual ~DemoCharacter() = default;
protected:
	//an enum class to hold the state of the character
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
	std::vector<Animation>animations;		//holds all the animations to the character
	State iCurState;						//the current state of the animation of the character
	int live;								//counts the lives of the character
};
