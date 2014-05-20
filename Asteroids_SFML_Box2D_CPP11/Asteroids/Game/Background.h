#pragma once
#include "Engine\GameObject.h"
#include "Player.h"

class Background : public GameObject
{
	
	void BeginContact(GameObject* object);
	void EndContact(GameObject* object);
	void Start();
	void Update(unsigned long frameNumber);

	string GetType();

public:
	
	Background() : GameObject(){}
	Background(string objectName, Engine* _Main, bool dynamic, bool physicsBody, Vector2 &_Position, string _TextureName, bool _IsSprite, int _Rows, int _Columns) : GameObject(objectName, _Main, dynamic, physicsBody, _Position, _TextureName, _IsSprite, _Rows, _Columns) {}

	void OnPointerPressed(Vector2 _Point);
	void OnPointerReleased(Vector2 _Point);
	void OnPointerMoved(Vector2 _Point);

	//Player* batman;
};

