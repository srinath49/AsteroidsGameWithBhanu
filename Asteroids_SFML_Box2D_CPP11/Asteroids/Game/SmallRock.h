#pragma once

#include "Engine\gameobject.h"
#include "AsteroidRock.h"

class SmallRock :
	public AsteroidRock
{	
public:

	void BlastRock();

	SmallRock() : AsteroidRock(){}

	SmallRock(string objectName, Engine* gameEngine, bool dynamic, bool physicsBody, Vector2 &_Position, string _TextureName, bool _IsSprite, int _Rows, int _Columns) : AsteroidRock(objectName, gameEngine, dynamic, physicsBody, _Position, _TextureName, _IsSprite, _Rows, _Columns) {}


private:
	void BeginContact(GameObject* object);
	void EndContact(GameObject* object);
	void Start();
	void Update(unsigned long frameNumber);

	string GetType();

};

