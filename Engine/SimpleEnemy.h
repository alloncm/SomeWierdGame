#pragma once
#include"2DCharacter.h"
#include"EnergyBall.h"
#include"FrameTime.h"
#include <memory>
#include<vector>
#include<typeinfo>
class SimpleEnemy : public D2Character
{
public:
	SimpleEnemy(std::string source, float spe, Vec2 p, int l = 3);
	SimpleEnemy& operator=(const SimpleEnemy& s);
	SimpleEnemy(const SimpleEnemy& s);//try to implemet this function cuase unique_ptr cant be cipied and this might be the problem
	void Update(float dt, Rect<int>border, std::vector<D2Character*> obs,D2Character* hero);
	virtual void SetDirection(const Vec2& dir)override;
	virtual bool Hit()override;
	virtual void Draw(Graphics& gfx)override;
	bool IsAlive();
	virtual ~SimpleEnemy() = default;
private:
	RectI GetRangeRect();
	void FireBall(const Vec2& dir);
	void DestroyBall(int i);
	void DestroyBalls(const Rect<int>& Border);
private:
	int lives;
	static constexpr int range = 100;
	std::vector<std::unique_ptr<EnergyBall>> balls;
	EnergyBall ball;
	FrameTimer ft;
	FrameTimer shooter;
	static constexpr float shootTime = 1.0f;
	float shootCount;
	//add fire ability
	//the layer walks to the hero if its outside of the range
	//shoots at the pkayer if he is insise the range
};
