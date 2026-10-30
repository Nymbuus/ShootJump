#include "Player.h"

Player::Player(int windowWidth, int windowHeight)
	: centerPosition{windowWidth / 19.2f, windowHeight / 10.8f},
	  velocity{InitVel},
	  width{Radius*2},
	  height{Radius*2},
	  gun{centerPosition, Radius}
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
	gun.update(centerPosition, Radius, deltaTime);
}

void Player::draw() {
	DrawCircle(centerPosition.x, centerPosition.y, Radius, BLUE);
	gun.draw(centerPosition, Radius);
}

void Player::reset() {
	centerPosition = InitPos;
	velocity = InitVel;
}

void Player::jump() {
	velocity.y = JumpStrength;
}

void Player::moveRight(float deltaTime, bool touchingGround) {
	if (touchingGround)
		velocity.x += GroundXAcceleration * deltaTime;
	else
		velocity.x += AirXAcceleration * deltaTime;
}

void Player::moveLeft(float deltaTime, bool touchingGround) {
	if (touchingGround)
		velocity.x -= GroundXAcceleration * deltaTime;
	else
		velocity.x -= AirXAcceleration * deltaTime;
}

void Player::deaccelerate(float deltaTime, bool touchingGround) {
	//Deaccelerates positive velocity.
	if (velocity.x > 0.0f)
	{
		if (touchingGround)
			velocity.x -= GroundXDeacceleration * deltaTime;
		else
			velocity.x -= AirXDeacceleration * deltaTime;

		if (velocity.x < 0.0f)
		{
			velocity.x = 0.0f;
		}
	}
	//Deaccelerates negative velocity.
	if (velocity.x < 0.0f)
	{
		if (touchingGround)
			velocity.x += GroundXDeacceleration * deltaTime;
		else
			velocity.x += AirXDeacceleration * deltaTime;

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

void Player::fireGun()
{
	Vector2 gunRotationCoordinates = gun.fireBullet(centerPosition);

	velocity.x = gunRotationCoordinates.x * RecoilStrength;
	velocity.y = gunRotationCoordinates.y * RecoilStrength;
}

Gun& Player::getPlayerGun()
{
	return gun;
}