#pragma once
#include"2DCharacter.h"
#include"EnergyBall.h"
#include"FrameTime.h"
#include <memory>
class SimpleEnemy : public D2Character
{
public:
	SimpleEnemy(std::string source, float spe, Vec2 p, int l = 1);
	SimpleEnemy(const SimpleEnemy& s) = default;
	void Update(float dt, Rect<int>border, std::vector<D2Character*> obs,D2Character* hero);
	virtual void SetDirection(const Vec2& dir)override;
	virtual bool Hit()override;
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
	const float shootTime = 1.0f;
	float shootCount;
	//add fire ability
	//the layer walks to the hero if its outside of the range
	//shoots at the pkayer if he is insise the range
};
