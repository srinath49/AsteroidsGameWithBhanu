#pragma once
#include "engine\gameobject.h"

class Player;

class Bullet :public GameObject
{
	
	void BeginContact(GameObject* object);

	void EndContact(GameObject* object);

	void Start();

	void Update(unsigned long frameNumber);

	string GetType(){return "Bullet";}

public:
	bool destroy;

	Bullet() : GameObject(){}

	Bullet(string objectName, Engine* gameEngine, bool dynamic, bool physicsBody, Vector2 &_Position, string _TextureName, bool _IsSprite, int _Rows, int _Columns) : GameObject(objectName, gameEngine, dynamic, physicsBody, _Position, _TextureName, _IsSprite, _Rows, _Columns) {}

	Player* playerRef;
	
	sf::Clock lifeClock;
};

