#include "Gun.h"
#include <iostream>

Gun::Gun(Vector2 playerCenterPosition, float playerRadius)
	: position{ playerCenterPosition.x + playerRadius - Width, playerCenterPosition.y - (Height / 2) },
	  rotation{InitRotation}
{
}

void Gun::update(Vector2 playerCenterPosition, float playerRadius)
{
	position = { playerCenterPosition.x + playerRadius - Width, playerCenterPosition.y - (Height / 2) };

	// Update the rotation of the gun.
	std::cout << "mouseposX: " << GetMousePosition().x << "  posY: " << GetMousePosition().y << std::endl;
}

void Gun::draw(Vector2 playerCenterPosition, float playerRadius)
{
	//DrawRectangle(position.x, position.y, Width, Height, BLACK);
	Rectangle gunRec = { position.x - playerRadius + Width, position.y + (Height / 2.0f) , Width, Height };
	DrawRectanglePro(gunRec, {Width - playerRadius, (Height / 2.0f)}, rotation, BLACK);
}