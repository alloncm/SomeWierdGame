#include "Obs.h"

Obs::Obs(std::string source, Vec2 position, Color bg, int width, int height, float speed)
	:
	D2Character(source,speed,position,{0,0},bg,width,height)
{
}


bool Obs::IsColliding(D2Character * ch)
{
	const Rect<int> r1 = this->GetRect();
	const Rect<int> r2 = ch->GetRect();
	return r1.IsColliding(r2);
}

void Obs::SetDirection(const Vec2 & v)
{
}
