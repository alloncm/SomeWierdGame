#include "Enemy.h"

Enemy::Enemy(std::string s, float spe, Vec2 p, int w, int h, Vec2_<int> searchStart, int animLong, float ht)
	:
	DemoCharacter(s,spe,p,w,h,searchStart,animLong,ht)
{
}

void Enemy::MoveEnemy(DemoCharacter& dc)
{

}

