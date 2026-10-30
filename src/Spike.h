#pragma once
#include "raylib.h"

enum class Direction
{
	North,
	South,
	West,
	East
};

class Spike
{
public:
	Spike(Vector2 spikePos, Direction spikePointDirection);

	void draw();

	Vector2 getPosition(int positionNr);

private:
	Vector2 position1{};
	Vector2 position2{};
	Vector2 position3{};

	float Width = 60.0f;
	float Height = 80.0f;

	void setPositions(Vector2 spikePos, Direction spikePointDirection);
	void getCollision();
};