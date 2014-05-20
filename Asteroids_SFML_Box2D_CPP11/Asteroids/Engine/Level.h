#pragma once

#include "Game/Game.h"
#include "GameObject.h"
#include <string>


using namespace std;

class Game;

enum LevelState
{
	LevelLoading,
	LevelLoaded,
	LevelInstruction,
	LevelRunning,
	LevelDone,
	LevelWin,
	LevelLose,
};

class Level
{
public:

	Level(){}
	Level(Game* gameEngine, int levelNumber);

	virtual void CreateLayers(){}
	virtual void CreateGameObjects(){}
	virtual void AddObjectsToLayers(){}
	virtual void DeleteAllGameObjects();
	virtual void LevelWon(){}
	virtual void LevelLost(){}
	virtual void Update(unsigned long frameNumber){}
	
	virtual void SetLevelState(LevelState newState);
	virtual LevelState GetLevelState();

	virtual void AddObjectToLayer(GameObject* gObj, int layer);
	virtual void Initialize();
	virtual void ReleaseAllResources();
	virtual void SetLevelTimer();

	/**
	 * This is called by the Controller class when it receives a PointerPress event.
	 * A pointer press event is fired when either a Tap or click occurs in the game.
	 *
	 * @param		_Point			The point in the game world where the event took place
	 */
	virtual void OnPointerPressed(Vector2 point){}

	/**
	 * This is called by the Controller class when it receives a PointerMoved event.
	 * A pointer moved event is fired when either a 'Tap and drag' or 'Click and Drag' takes place.
	 *
	 * @param		_Point			The current pointer position while in the pointer moved event
	 */
	virtual void OnPointerMoved(Vector2 point){}

	/**
	 * This is called by the Controller class when it receives a PointerReleased event.
	 * A pointer released event is fired when either an UnTap or click-released occurs in the game.
	 *
	 * @param		_Point			The point in the game world where the event took place
	 */
	virtual void OnPointerReleased(Vector2 point){}

	/**
	 * This is called by the Controller class when it receives a PointerPress event.
	 * A pointer press event is fired when either a Tap or click occurs in the game.
	 *
	 * @param		_Point			The point in the game world where the event took place
	 */
	virtual void OnKeyPressed(sf::Keyboard::Key key){}

	/**
	 * This is called by the Controller class when it receives a PointerReleased event.
	 * A pointer released event is fired when either an UnTap or click-released occurs in the game.
	 *
	 * @param		_Point			The point in the game world where the event took place
	 */
	virtual void OnKeyReleased(sf::Keyboard::Key key){}

	int levelNumber;
	Game* gameEngine;

	sf::Time timer;
	sf::Clock clock;

	LevelState currentState;
	LevelState previousState;

	list<GameObject*> levelObjs;

	list<GameObject*>::iterator levelObjsIterator; 

	bool layersAdded;
};
