#include "Platform.h"

Platform::Platform(Vector2 position, float width, float height, Color color)
	: position(position),
	  playerHitLeft{false},
	  width{width},
	  height{height},
	  color{color}
{
}

void Platform::draw()
{
	DrawRectangle(position.x, position.y, width, height, color);
}

Rectangle Platform::getCollisionRect() const
{
	return Rectangle(
		position.x,
		position.y,
		width,
		height
	);
}