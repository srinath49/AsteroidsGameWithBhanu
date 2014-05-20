#pragma once
#include "Engine\gameobject.h"
#include "GameLevel.h"


class AsteroidRock :
	public GameObject
{	
public:

	enum AsteroidState
	{
		NormalState,
		BlastState,
		DeadState
	};

	AsteroidRock() : GameObject(){}

	AsteroidRock(string objectName, Engine* gameEngine, bool dynamic, bool physicsBody, Vector2 &_Position, string _TextureName, bool _IsSprite, int _Rows, int _Columns) : GameObject(objectName, gameEngine, dynamic, physicsBody, _Position, _TextureName, _IsSprite, _Rows, _Columns) {this->gameEngine = gameEngine;}

	virtual void BlastRock(){}
	int GetScoreValue(){return scoreValue;}
	string GetType(){return "Asteroid";}

	void SetState(AsteroidState newState);

	AsteroidState GetState(){return currentState;}
	float RandFloatInRange(float a, float b){return ((b-a)*((float)rand()/RAND_MAX))+a;}

	void CheckCoordinates();
	GameLevel* currentLevel;

private:
	int scoreValue;

	virtual void BeginContact(GameObject* object){}
	virtual void EndContact(GameObject* object){}
	virtual void Start(){}
	virtual void Update(unsigned long frameNumber){}

protected:
	Engine* gameEngine;

	AsteroidState currentState;
	AsteroidState previousState;

};

