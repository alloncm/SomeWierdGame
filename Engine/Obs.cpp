#include "Obs.h"

Obs::Obs(std::string source, Vec2 position, Color bg, int width, int height, float speed)
	:
	D2Character(source,speed,position,{0,0},bg,width,height)
{
}


bool Obs::Hit()
{
	return false;
}

bool Obs::IsColliding(const Rect<int>& r)
{
	const Rect<int> r1 = this->GetRect();
	const Rect<int> r2 = r;
	return r1.IsColliding(r2);
}

void Obs::SetDirection(const Vec2 & v)
{
}
