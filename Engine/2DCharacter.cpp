#include "2DCharacter.h"

D2Character::D2Character(std::string source, float speed, Vec2 position, Vec2 vel, Color bg,int w,int h)
	:
	sprite(source),
	speed(speed),
	pos(position),
	vel(vel),
	backGround(bg),
	width(w),
	height(h)
{
	if (w == 0)
	{
		width = sprite.GetWidth();
	}
	if (h == 0)
	{
		height = sprite.GetHeight();
	}
}

void D2Character::Draw(Graphics & gfx)
{
	Color c = backGround;
	gfx.DrawSprite((int)pos.x, (int)pos.y, sprite, [ c ](Color src,int destX ,int destY,Graphics& gfx) {
		if (src != c)
		{
			gfx.PutPixel(destX,destY,src);
		}
	});
}

void D2Character::Update(float dt)
{
	pos += vel*dt;
}

int D2Character::GetWidth() const
{
	return this->width;
}

int D2Character::GetHeight() const
{
	return height;
}

const Rect<int> D2Character::GetRect() const
{
	return RectI({ (int)pos.x,(int)pos.y }, { (int)pos.x + width,(int)pos.y + height });
}

void D2Character::SetLocation(const Vec2 & p)
{
	pos.x = p.x;
	pos.y = p.y;
}

const Vec2 & D2Character::GetPosition() const
{
	return pos;
}
