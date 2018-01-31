#pragma once
#include"2DCharacter.h"
#include"EnergyBall.h"
#include"FrameTime.h"


//idea: the player will fire to a specific place chosen by the user other stick or mouse or keyboard, the player will have a white symbol to indicate where to shoot
class SimplePlayer : public D2Character
{
public:
	SimplePlayer(float spe, Vec2 p, EnergyBall& b);
	virtual void SetDirection(const Vec2& dir)override;
	virtual bool Hit()override;
	//Vec2 GetDirection();						
	void FireBall(Vec2& dir);
	virtual void Draw(Graphics& gfx)override;
	bool IsAlive();
	void Update(float dt, Rect<int>border, std::vector<D2Character*> obs, bool canMove);		//updates the player based on the border of the screen and destroys the balls out of the screen
	virtual ~SimplePlayer();
private:
	Vec2 GetBallMatchingPosition();
	void DestroyFireBall(Rect<int>Border);		//destroy the balls that are out of the rect border
	void DestroyBall(int i);					//destroy one specific ball
	void CreateBall();							//creates a ball
	static constexpr int lives = 10;
protected:
	EnergyBall ball;			//ball for example
	EnergyBall** balls;			// array of pointer to balls
	int countB;					// counts the num of balls 
	FrameTimer ft;				//frame timer for the balls
	int live;					//the lives of the character
};