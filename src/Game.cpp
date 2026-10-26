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
	ToggleFullscreen();
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
	if (IsKeyPressed(KEY_SPACE) && touchingGround)
	{
		player.jump();
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		player.fireGun();
	}

	if (IsKeyPressed(KEY_T))
	{
		ToggleFullscreen();
	}

	if (IsKeyDown(KEY_D))
	{
		player.moveRight(deltaTime, touchingGround);
	}
	else if (IsKeyDown(KEY_A))
	{
		player.moveLeft(deltaTime, touchingGround);
	}
	else
	{
		player.deaccelerate(deltaTime, touchingGround);
	}
}

// Updates everything that needs to be checked every frame.
void Game::update(float deltaTime) {
	touchingGround = false;

	Rectangle previousPlayerCollision = player.getCollisionRect();

	player.update(deltaTime);

	Rectangle playerCollision = player.getCollisionRect();

	// Checks collision between player and bullets towards all platforms.
	if (!platforms.empty())
	{
		for (int i = 0; i < platforms.size(); i++)
		{
			// Checks player and platforms
			Rectangle platformCollision = platforms.at(i).getCollisionRect();
			checkPlatformCollision(playerCollision, previousPlayerCollision, platformCollision);

			// Checks bullets and platforms
			std::vector<Bullet>& bullets = player.getPlayerGun().getBullets();
			if (!bullets.empty())
			{
				for (int j = 0; j < bullets.size(); j++)
				{
					Circle bulletColl = player.getPlayerGun().getBullets().at(j).getCollisionCircle();
					if (CheckCollisionCircleRec(bulletColl.center, bulletColl.radius, platformCollision))
					{
						bullets.erase(bullets.begin() + j);
					}
				}
			}
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
	Platform platform3({ 770.0f, windowHeight - 140.0f }, 100.0f, 50.0f, RED);
	platforms.emplace_back(platform3);
	Platform platform4({ 40.0f, windowHeight - 440.0f }, 100.0f, 50.0f, RED);
	platforms.emplace_back(platform4);
}

void Game::checkPlatformCollision(
	Rectangle playerCollision,
	Rectangle previousPlayerCollision,
	Rectangle platformCollision) {
	if (CheckCollisionRecs(playerCollision, platformCollision))
	{
		float previousLeft = previousPlayerCollision.x;
		float previousRight = previousLeft + previousPlayerCollision.width;
		float previousTop = previousPlayerCollision.y;
		float previousBottom = previousTop + previousPlayerCollision.height;

		float playerLeft = playerCollision.x;
		float playerRight = playerLeft + playerCollision.width;
		float playerTop = playerCollision.y;
		float playerBottom = playerTop + playerCollision.height;

		float platformLeft = platformCollision.x;
		float platformRight = platformLeft + platformCollision.width;
		float platformTop = platformCollision.y;
		float platformBottom = platformTop + platformCollision.height;

		// Land on top of the platform
		if (previousBottom <= platformTop && playerBottom >= platformTop)
		{
			player.hitVertical(platformTop - playerCollision.height);
			touchingGround = true;
		}
		// Hit the underside of the platform
		else if (previousTop >= platformBottom && playerTop <= platformBottom)
		{
			player.hitVertical(platformBottom);
		}
		// Hit the left side of the platform
		else if (previousRight <= platformLeft && playerRight >= platformLeft)
		{
			player.hitWall(platformLeft - playerCollision.width);
		}
		// Hit the right side of the platform
		else if (previousLeft >= platformRight && playerLeft <= platformRight)
		{
			player.hitWall(platformRight);
		}
	}
}