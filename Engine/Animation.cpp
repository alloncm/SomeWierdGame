#include "Animation.h"
#include"Effects.h"

Animation::Animation(int x, int y, int width, int height, int count, const Surface & s,float ht, Color chroma)
	:
	sprite(s),
	holdTime(ht),
	chroma(chroma)
{
	for (int i = 0; i < count; i++)
	{
		frames.emplace_back(RectI(x + width*i, y, width, height));
	}
}

void Animation::Update(float dt)
{
	curFrameTime += dt;
	while (curFrameTime >= holdTime)
	{
		Advance();
		curFrameTime -= holdTime;
	}
}

void Animation::Draw(const Location & l, Graphics & gfx)
{
	//negative effect
	gfx.DrawSprite(l.x, l.y, frames[iCurFrame], sprite,SpriteEffects::Chroma(chroma));
}

void Animation::Draw(const Location & l, Graphics & gfx, RectI & clip)
{
	SpriteEffects::Chroma e = { chroma };
	gfx.DrawSprite(l.x, l.y, frames[iCurFrame], clip, sprite, e);
}

void Animation::Advance()
{
	iCurFrame++;
	if (iCurFrame >= frames.size())
	{
		iCurFrame = 0;
	}
}
