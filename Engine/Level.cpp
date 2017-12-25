#include "Level.h"

Level::Level(Player* p,Graphics& g)
	:
	gfx(&g)
{
	hero = p;
}

void Level::Draw()
{
	hero->Draw(*gfx);
}

void Level::Update(const Vec2& dir,bool fire)
{
	float timer = ft.Mark();
	hero->Update(timer, gfx->GetScreenRect());
	hero->SetDirection(dir);
	if (fire)
	{
		hero->FireBall();
	}
}
