#include "Player.h"
#include <iostream>

Player::Player(int windowWidth, int windowheight)
	: position{windowWidth/19.2f, windowheight/10.8f},
	  velocity{InitVel}
{
}

void Player::update(float deltaTime) {
	velocity.y += Gravity * deltaTime;
	position.y += velocity.y * deltaTime;

	if (velocity.x > MaxVelocityX)
	{
		velocity.x = MaxVelocityX;
	}
	else if (velocity.x < -MaxVelocityX)
	{
		velocity.x = -MaxVelocityX;
	}

	position.x += velocity.x * deltaTime;
}

void Player::draw() {
	DrawRectangle(position.x, position.y, Width, Height, BLUE);
}

void Player::reset() {
	position = InitPos;
	velocity = InitVel;
}

void Player::jump() {
	velocity.y = JumpStrength;
}

void Player::moveRight(float deltaTime) {
	velocity.x += HorizontalAcceleration * deltaTime;
}

void Player::moveLeft(float deltaTime) {
	velocity.x -= HorizontalAcceleration * deltaTime;
}

void Player::deaccelerate(float deltaTime) {
	//Deaccelerates positive velocity.
	if (velocity.x > 0.0f)
	{
		velocity.x -= HorizontalAcceleration * deltaTime;
		if (velocity.x < 0.0f)
		{
			velocity.x = 0.0f;
		}
	}
	//Deaccelerates negative velocity.
	if (velocity.x < 0.0f)
	{
		velocity.x += HorizontalAcceleration * deltaTime;
		if (velocity.x > 0.0f)
		{
			velocity.x = 0.0f;
		}
	}
}

void Player::hitVertical(float stayPosY) {
	position.y = stayPosY;
	velocity.y = 0.0f;
}

void Player::hitWall(float stayPosX) {
	position.x = stayPosX;
	velocity.x = 0.0f;
}

Rectangle Player::getCollisionRect() const{
	return Rectangle(
		position.x,
		position.y,
		Width,
		Height
	);
}