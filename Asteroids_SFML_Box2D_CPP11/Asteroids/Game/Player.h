#pragma once

#include "Engine\GameObject.h"
#include "GameLevel.h"


class Player : public GameObject
{
public:
	enum MoveDirection
	{
		Up,
		Down,
		Right,
		Left
	};
	
	enum RotationAngle
	{
		Clock,
		Anti
	};
	

	enum  PlayerState
	{
		NormalState,
		DyingState,
		DeadState
	};

	int Score;
	GameLevel* currentLevel;
	int lives;
	float speed;

	Player() : GameObject(){}
	Player(string objectName, Engine* gameEngine, bool dynamic, bool physicsBody, Vector2 &_Position, string _TextureName, bool _IsSprite, int _Rows, int _Columns) : GameObject(objectName, gameEngine, dynamic, physicsBody, _Position, _TextureName, _IsSprite, _Rows, _Columns) {this->gameEngine = gameEngine;}

	void OnPointerPressed(Vector2 _Point);
	void OnPointerReleased(Vector2 _Point);
	void OnPointerMoved(Vector2 _Point);
	void OnKeyPressed(sf::Keyboard::Key pressedKey);
	void OnKeyReleased(sf::Keyboard::Key releasedKey);

	void SetState(PlayerState);
	PlayerState GetState(){return currentState;}
	
	void MovePlayer(MoveDirection direction);
	void RotatePlayer(RotationAngle angle);
	
	void AddScore(int _ScoreToAdd){Score+=_ScoreToAdd;}

	void Fire();

	void SlowMove();

	void SlowRotate();

	//string IntString(int intToConvert);

private:

	void BeginContact(GameObject* object);
	void EndContact(GameObject* object);
	void Start();
	void Update(unsigned long frameNumber);
	void OnDestroy();
	string GetType();

	void CheckCoordinates();

	PlayerState currentState;
	PlayerState previousState;

	//unsigned long tempframe;
	bool isTempframe;
	bool movedLastFrame;

	GameObject* ScoreObject;
	GameObject* EnemiesEscapedObject;
	GameObject* ScoreImage;
	GameObject* EscapedImage;

	int clickcount;

	Engine* gameEngine;

	Vector2 lookAtPoint;

	sf::Clock fireClock;
	sf::Time fireTimer;

	bool firstFire;
};

