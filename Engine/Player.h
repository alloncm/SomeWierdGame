#pragma once
#include"DemoCharacter.h"
#include"EnergyBall.h"
#include"FrameTime.h"
#include"FileNames.h"

class Player : public DemoCharacter
{
public:
	Player(float spe, Vec2 p, int w, int h, Vec2_<int> searchStart, int animLong, float ht,EnergyBall& b);
	void FireBall();
	void DestroyFireBall(Rect<int>Border);
	void Update(float dt, Rect<int>border);
	virtual void Draw(Graphics& gfx)override;
	virtual ~Player() = default;
private:
	Vec2 GetBallMatchingPosition();
protected:
	EnergyBall ball;
	EnergyBall** balls;
	int countB;
	FrameTimer ft;
};