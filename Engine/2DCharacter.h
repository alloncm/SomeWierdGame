#pragma once
#include"Surface.h"
#include"Graphics.h"
#include"Effects.h"
#include"SpritesManager.h"

//an abstract class to represent all the 2d objects and charachters in the game

class D2Character
{
public:
	D2Character& operator=(const D2Character& b) = default;
	virtual void Draw(Graphics& gfx);
	virtual void Update(float dt);
	virtual void SetDirection(const Vec2& v) = 0;
	int GetWidth()const;
	int GetHeight()const;
	const Rect<int> GetRect()const;
	void SetLocation(const Vec2& p);
	const Vec2& GetPosition()const;
	Vec2 GetUpdatedPosition(float dt);
	bool InsideScreen();
	virtual bool IsColliding(D2Character* obj);
	virtual bool Hit() = 0;							//return true if dead
	virtual ~D2Character() = default;
protected:
	D2Character() = default;
	D2Character(const D2Character&) = default;
	D2Character(std::string source, float speed, Vec2 position, Vec2 vel, Color bg);
protected:
	Surface* sprite;			//the sprite used to draw the character
	Vec2 pos;					//the position of the character
	Vec2 vel;					//the velocity direction of the character
	float speed;				//the speed of the character
	Color backGround;			//the background of the sprite to be removed
	
};