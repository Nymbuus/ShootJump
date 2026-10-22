#include "Gun.h"
#include <iostream>
#include <numbers>

Gun::Gun(Vector2 playerCenterPosition, float playerRadius)
	: position{ playerCenterPosition.x + playerRadius - Width, playerCenterPosition.y - (Height / 2) },
	  playerRadius{playerRadius},
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

Vector2 Gun::fireBullet(Vector2 playerCenterPosition)
{
	Vector2 coordinatePercentage = { 0.0f, 0.0f };
	coordinatePercentage.x = cosf(rotation * (std::numbers::pi_v<float> / 180.0f));
	coordinatePercentage.y = sinf(rotation * (std::numbers::pi_v<float> / 180.0f));

	Vector2 gunFrontMidPos = {0.0f, 0.0f};

	gunFrontMidPos.x = playerCenterPosition.x + playerRadius * coordinatePercentage.x;
	gunFrontMidPos.y = playerCenterPosition.y + playerRadius * coordinatePercentage.y;

	Bullet bullet(gunFrontMidPos, coordinatePercentage);
	bullets.emplace_back(bullet);

	return coordinatePercentage;
}

std::vector<Bullet>& Gun::getBullets()
{
	return bullets;
}

void Gun::deleteBullet()
{
	bullets.erase(bullets.begin());
}

float Gun::getRotation()
{
	return rotation;
}