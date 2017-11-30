#pragma once
#include"DemoCharacter.h"
#include"EnergyBall.h"
#include"FrameTime.h"

namespace FileNames
{
	const static std::string hero("knightTest32x48.bmp");
}
class Player : public DemoCharacter
{
public:
	Player(float spe, Vec2 p, int w, int h, Vec2_<int> searchStart, int animLong, float ht,EnergyBall& b);
	void FireBall();
	void DestroyFireBall(Rect<int>Border);
	void Update(float dt, Rect<int>border);
	virtual void Draw(Graphics& gfx)override;
private:
	Vec2 GetBallMatchingPosition();
protected:
	EnergyBall ball;
	EnergyBall** balls;
	int countB;
	FrameTimer ft;
};