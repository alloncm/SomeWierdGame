#pragma once
#include"2DCharacter.h"
#include"EnergyBall.h"
#include"FrameTime.h"

class SimplePlayer : public D2Character
{
public:
	SimplePlayer(float spe, Vec2 p, int w, int h, EnergyBall& b);
	void FireBall();
	void Update(float dt, Rect<int>border, std::vector<D2Character*> obs, bool canMove);		//updates the player based on the border of the screen and destroys the balls out of the screen
	virtual void Draw(Graphics& gfx)override;
	virtual ~SimplePlayer();
private:
	Vec2 GetBallMatchingPosition();
	void DestroyFireBall(Rect<int>Border);		//destroy the ball
	static constexpr int lives = 10;
protected:
	EnergyBall ball;			//ball for example
	EnergyBall** balls;			// array of pointer to balls
	int countB;					// counts the num of balls 
	FrameTimer ft;				//frame timer for the balls
};