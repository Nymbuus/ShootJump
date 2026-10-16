#include "raylib.h"

class Platform
{
public:
	Platform(Vector2 position, float width, float height, Color color);

	void draw();
	
	Rectangle getCollisionRect() const;

private:
	Vector2 position;

	bool playerHitLeft;

	float width;
	float height;
	Color color;
};