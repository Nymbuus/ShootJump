#include "Bullet.h"

Bullet::Bullet(Vector2 gunFrontPos, float gunRotation)
	: position{gunFrontPos},
	  rotation{gunRotation}
{
}

void Bullet::update(float deltaTime)
{
	position.x += Velocity * deltaTime;
	position.y += Velocity * deltaTime;
}

void Bullet::draw()
{
	Rectangle bulletrec = { position.x, position.y, Width, Height };
	DrawRectanglePro(bulletrec, position, rotation, YELLOW);
}