#pragma once
#include "raylib.h"
#include "Platform.h"
#include "Player.h"
#include <vector>

class Game
{
public:
	Game();

	void run();

private:
	Player player;

	static constexpr int InitWindowWidth = 1920;
	static constexpr int InitWindowHeight = 1080;
	static constexpr int InitFPS = 60;
	static constexpr float MaxFrameTime = 0.0333f;

	int windowWidth;
	int windowHeight;

	std::vector<Platform> platforms;
	bool jumpReady = false;
	float CollisionOffset = 5.0f;

	void processInput(float deltaTime);
	void update(float deltaTime);
	void draw();

	void createWalls();
	void createPlatforms();

	void checkPlatformCollision(
		Rectangle playerCollision,
		Rectangle previousPlayerCollision,
		Rectangle platformCollision);
};