#include "Player.h"

Player::Player(int windowWidth, int windowheight)
	: centerPosition{windowWidth/19.2f, windowheight/10.8f},
	  velocity{InitVel},
	  width{Radius*2},
	  height{Radius*2}
{
}

void Player::update(float deltaTime) {
	velocity.y += Gravity * deltaTime;
	centerPosition.y += velocity.y * deltaTime;

	if (velocity.x > MaxVelocityX)
	{
		velocity.x = MaxVelocityX;
	}
	else if (velocity.x < -MaxVelocityX)
	{
		velocity.x = -MaxVelocityX;
	}

	centerPosition.x += velocity.x * deltaTime;
}

void Player::draw() {
	DrawCircle(centerPosition.x, centerPosition.y, Radius, BLUE);
}

void Player::reset() {
	centerPosition = InitPos;
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
	centerPosition.y = stayPosY + Radius; 
	velocity.y = 0.0f;
}

void Player::hitWall(float stayPosX) {
	centerPosition.x = stayPosX + Radius;
	velocity.x = 0.0f;
}

Rectangle Player::getCollisionRect() const{
	return Rectangle(
		centerPosition.x - Radius,
		centerPosition.y - Radius,
		width,
		height
	);
}