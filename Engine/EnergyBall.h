#pragma once
#include "Surface.h"
#include"Graphics.h"
#include "Effects.h"
#include "2DCharacter.h"
class EnergyBall : public D2Character
{
private:
	Vec2 direc;
public:
	EnergyBall(std::string source,float speed,Vec2 position,Vec2 dir);
	EnergyBall() = default;
	EnergyBall& operator=(EnergyBall& b) = default;
	virtual void SetDirection(const Vec2& v) override;
	virtual void Update(float dt)override;
};