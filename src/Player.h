#pragma once
#include "raylib.h"
#include "Gun.h"

class Player
{
public:
	Player(int windowWidth, int windowHeight);

	void update(float deltaTime);
	void draw();
	void reset();

	void jump();
	void moveRight(float deltaTime);
	void moveLeft(float deltaTime);
	void deaccelerate(float deltaTime);
	void hitVertical(float stayPosY);
	void hitWall(float StayPosX);
	void fireGun();

	Rectangle getCollisionRect() const;

private:
	Vector2 centerPosition;
	Vector2 velocity;
	float width;
	float height;
	Gun gun;

	static constexpr Vector2 InitVel = { 0.0f, 0.0f };
	static constexpr Vector2 InitPos = { 100.0f, 480.0f };
	static constexpr float JumpStrength = -1000.0f;
	static constexpr float HorizontalAcceleration = 3300.0f;
	static constexpr float MaxVelocityX = 500.0f;
	static constexpr float Radius = 25.0f;
	static constexpr float Gravity = 2800.0f;
};