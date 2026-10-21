#pragma once
#include "raylib.h"

class Bullet
{
public:
	Bullet(Vector2 gunFrontMidPos, Vector2 coordinatePercentage);

	void update(float deltaTime);
	void draw();
	void reset();

private:
	Vector2 position;
	Vector2 velocity;

	static constexpr float MaxVelocity = 500.0f;
	static constexpr float Radius = 8.0f;
};