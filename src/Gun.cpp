#include "Gun.h"
#include <iostream>
#include <numbers>

Gun::Gun(Vector2 playerCenterPosition, float playerRadius)
	: position{ playerCenterPosition.x + playerRadius - Width, playerCenterPosition.y - (Height / 2) },
	  rotation{InitRotation},
	  deltaX{0.0f},
	  deltaY{0.0f}
{
}

void Gun::update(Vector2 playerCenterPosition, float playerRadius, float deltaTime)
{
	position = { playerCenterPosition.x + playerRadius - Width, playerCenterPosition.y - (Height / 2) };

	// Update the rotation of the gun.
	Vector2 mousePos = GetMousePosition();
	deltaX = mousePos.x - playerCenterPosition.x;
	deltaY = mousePos.y - playerCenterPosition.y;
	rotation = atan2f(deltaY, deltaX) * (180.0f / std::numbers::pi_v<float>);

	if (!bullets.empty())
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets.at(i).update(deltaTime);
		}
	}
}

void Gun::draw(Vector2 playerCenterPosition, float playerRadius)
{
	Rectangle gunRec = { position.x - playerRadius + Width, position.y + (Height / 2.0f) , Width, Height };
	DrawRectanglePro(gunRec, {Width - playerRadius, (Height / 2.0f)}, rotation, BLACK);

	if (!bullets.empty())
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets.at(i).draw();
		}
	}
}

void Gun::fireBullet()
{
	Bullet bullet({ position.x + Width, position.y + (Height / 2.0f)}, rotation, deltaX, deltaY);
	bullets.emplace_back(bullet);
}