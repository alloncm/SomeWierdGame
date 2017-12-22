#include "Level.h"

Level::Level(Player p, std::string bg)
	:
	hero(p),
	backGround(bg)
{
}

void Level::Draw(Graphics & gfx)
{
	hero.Draw(gfx);
	gfx.DrawSprite(0, 0, backGround, [this](Color cSrc, int xDest, int yDest, Graphics& gfx) {});
}
