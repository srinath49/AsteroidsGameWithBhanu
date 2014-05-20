#pragma once
#include "Engine\level.h"


class GameLevel :
	public Level
{
public:
	GameLevel(void) : Level(){}
	GameLevel(Game* gameEngine, int levelNumber) : Level (gameEngine, levelNumber){}

	virtual void CreateLayers(){}
	virtual void CreateGameObjects(){}
	virtual void AddObjectsToLayers(){}
	virtual void LevelWon(){}
	virtual void LevelLost(){}
	virtual void Update(unsigned long frameNumber){}

	virtual void PlayerNull(){}

	virtual void OnPointerPressed(Vector2 point){}

	virtual void OnPointerMoved(Vector2 point){}

	virtual void OnPointerReleased(Vector2 point){}

	virtual void OnKeyPressed(sf::Keyboard::Key key){}

	virtual void OnKeyReleased(sf::Keyboard::Key key){}

	int enemiesCount;
	int rocksCount;
};

