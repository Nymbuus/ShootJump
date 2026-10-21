#include "Bullet.h"
#include <algorithm>
#include <numbers>
#include <iostream>

Bullet::Bullet(Vector2 gunFrontMidPos, Vector2 coordinatePercentage)
	: position{gunFrontMidPos}
{
	velocity.x = MaxVelocity * coordinatePercentage.x;
	velocity.y = MaxVelocity * coordinatePercentage.y;
}

void Bullet::update(float deltaTime)
{
	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;
}

void Bullet::draw()
{
	DrawCircle(position.x, position.y, Radius, PURPLE);
}