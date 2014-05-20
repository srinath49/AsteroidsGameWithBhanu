#pragma once

#include "Engine/Engine.h"
#include "Engine/LevelManager.h"

class LevelManager;

enum GameState
{
	RequestForLevelLoad,
	LoadTheLevel,
	ReloadTheLevel,
	LoadTheNextLevel,
	LoadingLevel,
	RunningLevel,
};


/**
 * The Game is the sub-class of the Engine class. It is the Highest level game-loop class to which the users have direct access. 
 * It hides all the Engine Level routines, like Layers, Physics, Rendering etc. 
 * Note: The Engine class is the Mid-Level game-loop class that hides the Windows Metro Specific routines, integration of the Box2D physics engine, etc.
 * The Game is where the users are supposed handle their game-specifc logics, create there game-specific objects etc.
 */
class Game :
	public Engine
{

public:

	/**
	 * The engine calles the Start function at the start of the game. 
	 * This is where all the game related initialization should be done.
	 */
	void Start();

	/**
	 * The Update function on the Game is called by the Engine each frame.
	 * This is where your game loop should exist.
	 *
	 * @param		frameNumber			The value of the current frame
	 */
	void Update(unsigned long frameNumber);

	/**
	 * This is called by the Controller class when it receives a PointerPress event.
	 * A pointer press event is fired when either a Tap or click occurs in the game.
	 *
	 * @param		_Point			The point in the game world where the event took place
	 */
	void OnPointerPressed(Vector2 point);

	/**
	 * This is called by the Controller class when it receives a PointerMoved event.
	 * A pointer moved event is fired when either a 'Tap and drag' or 'Click and Drag' takes place.
	 *
	 * @param		_Point			The current pointer position while in the pointer moved event
	 */
	void OnPointerMoved(Vector2 point);

	/**
	 * This is called by the Controller class when it receives a PointerReleased event.
	 * A pointer released event is fired when either an UnTap or click-released occurs in the game.
	 *
	 * @param		_Point			The point in the game world where the event took place
	 */
	void OnPointerReleased(Vector2 point);

	/**
	 * This is called by the Controller class when it receives a PointerPress event.
	 * A pointer press event is fired when either a Tap or click occurs in the game.
	 *
	 * @param		_Point			The point in the game world where the event took place
	 */
	void OnKeyPressed(sf::Keyboard::Key key);

	/**
	 * This is called by the Controller class when it receives a PointerReleased event.
	 * A pointer released event is fired when either an UnTap or click-released occurs in the game.
	 *
	 * @param		_Point			The point in the game world where the event took place
	 */
	void OnKeyReleased(sf::Keyboard::Key key);

	/**
	 *
	 */
	void SetGameState(GameState newState);

	/**
	 *
	 */
	GameState GetGameState();

	void RequestLevelLoad(int levelToLoad);
	void RequestLevelReload(int levelToLoad);
	void RequestNextLevelLoad();

private:
	
	/**  */
	LevelManager* levelManager;
	/**  */
	int previousLevel;
	/**  */
	int currentLevel;
	/**  */
	int levelToLoad;
	/**  */
	GameState previousState;
	/**  */
	GameState currentState;
	/**  */
	unsigned long loadRequestedFrame;

	/**
	 *
	 */
	void LoadLevel(int level);

	/**
	 *
	 */
	void UnLoadLevel(int level);

	/**
	 *
	 */
	void LoadNextLevel();

	/**
	 *
	 */
	void RestartLevel();

};
