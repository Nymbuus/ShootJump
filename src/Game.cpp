#include "Game.h"
#include <algorithm>
#include <iostream>

Game::Game()
	: player(InitWindowWidth, InitWindowHeight),
	  windowWidth{InitWindowWidth},
	  windowHeight{InitWindowHeight}
{
	InitWindow(InitWindowWidth, InitWindowHeight, "Platformer");
	SetTargetFPS(InitFPS);
	//ToggleFullscreen();
	createWalls();
	createPlatforms();
	run();
}

// Runs the whole gameloop.
void Game::run() {
	while (!WindowShouldClose())
	{
		float deltaTime = GetFrameTime();
		deltaTime = std::min(deltaTime, MaxFrameTime);
		processInput(deltaTime);
		update(deltaTime);
		draw();
	}

	CloseWindow();
}

// Process all inputs and acts accordingly.
void Game::processInput(float deltaTime) {
	if (IsKeyPressed(KEY_SPACE) && jumpReady)
	{
		player.jump();
	}

	if (IsKeyPressed(KEY_T))
	{
		ToggleFullscreen();
	}

	if (IsKeyDown(KEY_D))
	{
		player.moveRight(deltaTime);
	}
	else if (IsKeyDown(KEY_A))
	{
		player.moveLeft(deltaTime);
	}
	else
	{
		player.deaccelerate(deltaTime);
	}
}

// Updates everything that needs to be checked every frame.
void Game::update(float deltaTime) {
	jumpReady = false;

	Circle previousPlayerCollision = player.getCollisionRect();

	player.update(deltaTime);

	Circle playerCollision = player.getCollisionRect();

	std::cout << "playerPosX: " << previousPlayerCollision.center.x << "  posY: " << previousPlayerCollision.center.y <<
		"  lowerplatfomrY: " << platforms.at(1).getCollisionRect().y << std::endl;

	// Checks collision between player and all platforms.
	if (!platforms.empty())
	{
		for (int i = 0; i < platforms.size(); i++)
		{
			Rectangle platformCollision = platforms.at(i).getCollisionRect();
			checkPlatformCollision(playerCollision, previousPlayerCollision, platformCollision);
		}
	}
}

void Game::draw() {
	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawText("Platformer", 300, 10, 30, BLACK);

	player.draw();
	if(!platforms.empty())
	{
		for (int i = 0; i < platforms.size(); i++)
			platforms.at(i).draw();
	}
	EndDrawing();
}

void Game::createWalls() {
	Platform platformLeftWall({ 0.0f, 0.0f }, 30.0f, windowHeight, ORANGE);
	platforms.emplace_back(platformLeftWall);
	Platform platformRightWall({ windowWidth - 30.0f, 0.0f }, 30.0f, windowHeight, ORANGE);
	platforms.emplace_back(platformRightWall);
}

void Game::createPlatforms() {
	Platform floor({ 0.0f, windowHeight - 50.0f }, windowWidth, 50.0f, GREEN);
	platforms.emplace_back(floor);
	Platform platform({ 400.0f, windowHeight - 180.0f }, 100.0f, 50.0f, RED);
	platforms.emplace_back(platform);
	Platform platform2({ 470.0f, windowHeight - 250.0f }, 100.0f, 50.0f, RED);
	platforms.emplace_back(platform2);
}

void Game::checkPlatformCollision(
	Circle playerCollision,
	Circle previousPlayerCollision,
	Rectangle platformCollision) {
	if (CheckCollisionCircleRec(playerCollision.center, playerCollision.radius, platformCollision))
	{
		float previousLeft = previousPlayerCollision.center.x - previousPlayerCollision.radius;
		float previousRight = previousPlayerCollision.center.x + previousPlayerCollision.radius;
		float previousTop = previousPlayerCollision.center.y - previousPlayerCollision.radius;
		float previousBottom = previousPlayerCollision.center.y + previousPlayerCollision.radius;

		float playerLeft = playerCollision.center.x - playerCollision.radius;
		float playerRight = playerCollision.center.x + playerCollision.radius;
		float playerTop = playerCollision.center.y - playerCollision.radius;
		float playerBottom = playerCollision.center.y + playerCollision.radius;

		float platformLeft = platformCollision.x;
		float platformRight = platformLeft + platformCollision.width;
		float platformTop = platformCollision.y;
		float platformBottom = platformTop + platformCollision.height;

		// Land on top of the platform
		if (previousBottom <= platformTop && playerBottom >= platformTop)
		{
			player.hitVertical(platformTop - playerCollision.radius);
			jumpReady = true;
		}
		// Hit the underside of the platform
		else if (previousTop >= platformBottom && playerTop <= platformBottom)
		{
			player.hitVertical(platformBottom + playerCollision.radius);
		}
		// Hit the left side of the platform
		else if (previousRight <= platformLeft && playerRight >= platformLeft)
		{
			player.hitWall(platformLeft - playerCollision.radius);
		}
		// Hit the right side of the platform
		else if (previousLeft >= platformRight && playerLeft <= platformRight)
		{
			player.hitWall(platformRight + playerCollision.radius);
		}
	}
}