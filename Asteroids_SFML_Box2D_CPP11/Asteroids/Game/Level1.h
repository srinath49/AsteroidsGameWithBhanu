#pragma once

#include "GameLevel.h"
#include "Engine/GameObject.h"
#include "Player.h"
#include "BigRock.h"
#include "Background.h"

class Level1 : public GameLevel
{
public:
	Level1(void) : GameLevel(){levelDone = false;}
	Level1(Game* gameEngine, int levelNumber) : GameLevel (gameEngine, levelNumber){levelDone = false;}

	void CreateLayers();
	void CreateGameObjects();
	void AddObjectsToLayers();
	void LevelWon();
	void LevelLost();
	void Update(unsigned long frameNumber);

	void PlayerNull();

	void OnPointerPressed(Vector2 point);

	void OnPointerMoved(Vector2 point);

	void OnPointerReleased(Vector2 point);

	void OnKeyPressed(sf::Keyboard::Key key);

	void OnKeyReleased(sf::Keyboard::Key key);

	bool levelDone;
	int rocksLayer;
	int enemyLayer;

private:
	// Layer numbers
	int backgroundLayer;
	int playerLayer;

	Player* player;

	BigRock* bigRock1;
	
	Background* screenBackground;
};
