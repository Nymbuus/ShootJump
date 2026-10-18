#include "Gun.h"

Gun::Gun(Vector2 initPositon)
	: postion{initPositon},
	  rotation{InitRotation}
{
}

void Gun::update()
{
}

void Gun::draw()
{
	DrawRectangle(postion.x, postion.y, Width, Height, BLACK);
}