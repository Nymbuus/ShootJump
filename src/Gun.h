#pragma once
#include "raylib.h"
#include "Bullet.h"
#include <vector>

class Gun
{
public:
	Gun(Vector2 playerCenterPosition, float playerRadius);

	void update(Vector2 playerCenterPosition, float playerRadius, float delatTime);
	void draw(Vector2 playerCenterPosition, float playerRadius);

	Vector2 fireBullet(Vector2 playerCenterPosition);
	std::vector<Bullet>& getBullets();
	void deleteBullet();
	float getRotation();

private:
	Vector2 position;
	float rotation;
	std::vector<Bullet> bullets;

	float deltaX;
	float deltaY;
	float playerRadius;

	static constexpr float InitRotation = 0.0f;
	static constexpr float Width = 15.0f;
	static constexpr float Height = 10.0f;
};