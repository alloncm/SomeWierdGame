#pragma once
#include"Animation.h"


class DemoCharacter
{
public:
	DemoCharacter(std::string s, float spe, Vec2 p, int w, int h, Vec2_<int> searchStart,int animLong,float ht);
	void Draw(Graphics& gfx);
	void Update(float dt);
	void SetDirections(const Vec2& dir);
	const Vec2 GetDirection() const;
	RectI GetCharacterRect()const;
	void SetPosition(const Vec2& p);
	const Vec2& GetPosition();
	int GetHeight();
	int GetWidth();

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
	Surface sprite;
	std::vector<Animation>animations;
	Vec2 pos;
	Vec2 vel;
	int width;
	int height;
	float speed;
	State iCurState;

};
