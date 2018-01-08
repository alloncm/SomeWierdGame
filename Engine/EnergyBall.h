#pragma once
#include "Surface.h"
#include"Graphics.h"
#include "Effects.h"
#include "2DCharacter.h"
#include"FileNames.h"
class EnergyBall : public D2Character
{
public:
	EnergyBall(float speed,Vec2 position,Vec2 dir);	
	EnergyBall(const EnergyBall& other) = default;
	EnergyBall() = default;
	EnergyBall& operator=(const EnergyBall& b) = default;
	virtual bool Hit()override;
	virtual void SetDirection(const Vec2& v) override;
	virtual void Update(float dt)override;
	virtual ~EnergyBall() = default;
};