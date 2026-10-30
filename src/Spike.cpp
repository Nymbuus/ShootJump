#include "Spike.h"

// spikePos is the postion in the middle of the bottom of the triangle. Essentially in the middle of the short side.
Spike::Spike(Vector2 spikePos, Direction spikePointDirection)
{
	setPositions(spikePos, spikePointDirection);
}

void Spike::draw()
{
	DrawTriangle(position1, position2, position3, BLACK);
}

void Spike::setPositions(Vector2 spikePos, Direction spikePointDirection)
{
	if (spikePointDirection == Direction::North)
	{
		position1.x = spikePos.x;
		position1.y = spikePos.y - Height;

		position2.x = spikePos.x - (Width/2.0f);
		position2.y = spikePos.y;

		position3.x = spikePos.x + (Width/2.0f);
		position3.y = spikePos.y;
	}
	else if (spikePointDirection == Direction::South)
	{
		position1.x = spikePos.x - (Width / 2.0f);
		position1.y = spikePos.y;

		position2.x = spikePos.x;
		position2.y = spikePos.y + Height;

		position3.x = spikePos.x + (Width / 2.0f);
		position3.y = spikePos.y;
	}
	else if (spikePointDirection == Direction::West)
	{
		position1.x = spikePos.x;
		position1.y = spikePos.y - (Width / 2.0f);

		position2.x = spikePos.x - Height;
		position2.y = spikePos.y;

		position3.x = spikePos.x;
		position3.y = spikePos.y + (Width / 2.0f);
	}
	else if (spikePointDirection == Direction::East)
	{
		position1.x = spikePos.x;
		position1.y = spikePos.y - (Width / 2.0f);

		position2.x = spikePos.x;
		position2.y = spikePos.y + (Width / 2.0f);

		position3.x = spikePos.x + Height;
		position3.y = spikePos.y;
	}
}

void Spike::getCollision()
{
	
}

Vector2 Spike::getPosition(int positionNr)
{
	switch (positionNr)
	{
	case (1):
		return position1;
	case (2):
		return position2;
	case (3):
		return position3;
	default:
		break;
	}
}