#include "SimplePlayer.h"
//need to add string for sprite
SimplePlayer::SimplePlayer(float spe, Vec2 p, int w, int h, EnergyBall & b)
	:
	D2Character("put here the string for the source",spe,p,vel,Colors::Magenta,w,h)
{
	ball = b;
}

void SimplePlayer::FireBall()
{
}
