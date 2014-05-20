#pragma once

#include "Engine\gameobject.h"
#include "AsteroidRock.h"

class BigRock :
	public AsteroidRock
{	
public:

	string medRockATexture;
	string medRockBTexture;

	string smallRock1ATexture;
	string smallRock2ATexture;
	string smallRock3ATexture;

	string smallRock1BTexture;
	string smallRock2BTexture;
	string smallRock3BTexture;

	BigRock() : AsteroidRock(){}
	BigRock(string objectName, Engine* gameEngine, bool dynamic, bool physicsBody, Vector2 &_Position, string _TextureName, bool _IsSprite, int _Rows, int _Columns) : AsteroidRock(objectName, gameEngine, dynamic, physicsBody, _Position, _TextureName, _IsSprite, _Rows, _Columns) {}

	void BlastRock();

	string GetType();

private:
	void BeginContact(GameObject* object);
	void EndContact(GameObject* object);
	void Start();
	void Update(unsigned long frameNumber);

};

