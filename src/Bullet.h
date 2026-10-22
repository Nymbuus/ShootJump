#pragma once
#include "raylib.h"
#include "Circle.h"
#include <vector>

class Bullet
{
public:
	Bullet(Vector2 gunFrontMidPos, Vector2 coordinatePercentage);

	void update(float deltaTime);
	void draw();

	Circle getCollisionCircle();

private:
	Vector2 position;
	Vector2 velocity;

	static constexpr float MaxVelocity = 90.0f;
	static constexpr float Radius = 8.0f;
};