#include "Level.h"

Level::Level( std::string bg,Player* p)
	:
	backGround(bg)
{
	hero = p;
}

void Level::Draw(Graphics & gfx)
{
	
	gfx.DrawSprite(0, 0, backGround, [this](Color cSrc, int xDest, int yDest, Graphics& gfx) {
		gfx.PutPixel(xDest, yDest,
		{ cSrc.GetR(),cSrc.GetG(), cSrc.GetB() }
		);
	});
	hero->Draw(gfx);
}
