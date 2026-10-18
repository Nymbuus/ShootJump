#pragma once
#include "raylib.h"

class Gun
{
public:
	Gun(Vector2 initPostion);

	void update();
	void draw();
	void reset();

private:
	Vector2 postion;
	float rotation;

	static constexpr float InitRotation = 0.0f;
	static constexpr float Width = 10.0f;
	static constexpr float Height = 15.0f;
};