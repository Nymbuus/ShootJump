#pragma once
#include "raylib.h"

class Bullet
{
public:
	Bullet(Vector2 gunFrontPos, float gunRotation, float xDelta, float yDelta);

	void update(float deltaTime);
	void draw();
	void reset();

private:
	Vector2 position;
	float angle;
	float xVelocity;
	float yVelocity;

	static constexpr float MaxVelocity = 500.0f;
	static constexpr float Radius = 8.0f;
};