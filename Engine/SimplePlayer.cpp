#include "SimplePlayer.h"
//need to add string for sprite
SimplePlayer::SimplePlayer(float spe, Vec2 p, int w, int h, EnergyBall & b)
	:
	D2Character(FileNames::SHero , spe, p, vel, Colors::Magenta, w, h),
	live(lives)
{
	ball = b;
	balls = new EnergyBall*[countB];
}

void SimplePlayer::SetDirection(const Vec2 & dir)
{
	Vec2 d = dir;
	d.Normalize();
	vel = d*speed;
}

bool SimplePlayer::Hit()
{
	live--;
	return live == 0;
}

SimplePlayer::~SimplePlayer()
{
	for (int i = 0; i < countB; i++)
	{
		delete balls[i];
		balls[i] = nullptr;
	}
	delete[] balls;
}


