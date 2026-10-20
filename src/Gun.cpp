#include "Gun.h"
#include <iostream>
#include <numbers>

Gun::Gun(Vector2 playerCenterPosition, float playerRadius)
	: position{ playerCenterPosition.x + playerRadius - Width, playerCenterPosition.y - (Height / 2) },
	  rotation{InitRotation}
{
}

void Gun::update(Vector2 playerCenterPosition, float playerRadius)
{
	position = { playerCenterPosition.x + playerRadius - Width, playerCenterPosition.y - (Height / 2) };

	// Update the rotation of the gun.
	Vector2 mousePos = GetMousePosition();
	float deltaX = mousePos.x - playerCenterPosition.x;
	float deltaY = mousePos.y - playerCenterPosition.y;
	rotation = atan2f(deltaY, deltaX) * (180.0f / std::numbers::pi_v<float>);
}

void Gun::draw(Vector2 playerCenterPosition, float playerRadius)
{
	Rectangle gunRec = { position.x - playerRadius + Width, position.y + (Height / 2.0f) , Width, Height };
	DrawRectanglePro(gunRec, {Width - playerRadius, (Height / 2.0f)}, rotation, BLACK);
}

void Gun::fireBullet()
{
	Bullet bullet({ position.x + Width, position.y }, rotation);
}