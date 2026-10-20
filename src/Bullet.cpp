#include "Bullet.h"
#include <algorithm>
#include <numbers>
#include <iostream>

Bullet::Bullet(Vector2 gunFrontPos, float gunRotation, float xDelta, float yDelta)
	: position{gunFrontPos},
	  angle{gunRotation}
{
	float xPercentage = sinf(angle * (std::numbers::pi_v<float> / 180.0f));
	float yPercentage = cosf(angle * (std::numbers::pi_v<float> / 180.0f));
	xVelocity = MaxVelocity * xPercentage;
	yVelocity = MaxVelocity * yPercentage;
}

void Bullet::update(float deltaTime)
{
	position.x += xVelocity * deltaTime;
	position.y += yVelocity * deltaTime;
}

void Bullet::draw()
{
	DrawCircle(position.x, position.y, Radius, PURPLE);
}