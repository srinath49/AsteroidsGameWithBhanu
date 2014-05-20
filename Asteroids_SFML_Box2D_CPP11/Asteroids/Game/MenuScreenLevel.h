#pragma once
#include "Engine/Level.h"
#include "Background.h"

class MenuScreenLevel :
	public Level
{
public:
	MenuScreenLevel(void){}
	MenuScreenLevel(Game* _Main, int _LevelNumber) : Level (_Main, _LevelNumber){}

	void CreateLayers();
	void CreateGameObjects();
	void AddObjectsToLayers();
	void LevelWon();
	void LevelLost();
	void Update(unsigned long frameNumber);

	void OnPointerPressed(Vector2 point);

	void OnPointerMoved(Vector2 point);

	void OnPointerReleased(Vector2 point);

	void OnKeyPressed(sf::Keyboard::Key key);

	void OnKeyReleased(sf::Keyboard::Key key);


private:
	// Layer numbers
	int backgroundLayer;

	Background* screenBackground;
	Background* screenMessage;
};

