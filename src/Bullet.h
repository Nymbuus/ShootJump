#pragma once
#include "raylib.h"

class Bullet
{
public:
	Bullet(Vector2 gunFrontPos, float gunRotation);

	void update(float deltaTime);
	void draw();
	void reset();

private:
	Vector2 position;
	float rotation;

	static constexpr float Velocity = 500.0f;
	static constexpr float Width = 10.0f;
	static constexpr float Height = 5.0f;
};