#include "AsteroidRock.h"

void AsteroidRock::SetState(AsteroidState newState)
{
	previousState = currentState;
	currentState = newState;
}

void AsteroidRock::CheckCoordinates()
{
	if(position.x < -10.0f)
	{
		SetPosition(9.5f, position.y);
	}
	else if(position.x > 10.0f)
	{
		SetPosition(-9.5f, position.y);
	}

	if(position.y < -8.0f)
	{
		SetPosition(position.x, 7.5f);
	}
	else if(position.y > 8.0f)
	{
		SetPosition(position.x, -7.5f);
	}
}