
#include "Level.h"

Level::Level(Game* gameEngine, int levelNumber)
{
	layersAdded = false;
	this->levelNumber = levelNumber;
	this->gameEngine = gameEngine;
	SetLevelState(LevelLoading);
}

void Level::Initialize()
{
	CreateLayers();
	CreateGameObjects();
	AddObjectsToLayers();
}

void Level::ReleaseAllResources()
{
	//m_Timer = nullptr;
	DeleteAllGameObjects();
}

void Level::AddObjectToLayer(GameObject* gObj, int layer)
{
	gameEngine->GetLayer(layer)->AddObjectToLayer(gObj);
}

void Level::SetLevelTimer()
{
	//m_Timer = ((App^)Application::Current->Current)->GetAppTimer();
}

void Level::SetLevelState(LevelState newState)
{
	previousState = currentState;
	currentState = newState;
}

LevelState Level::GetLevelState()
{
	return currentState;
}

void Level::DeleteAllGameObjects()
{
	for(int i = 0; i <= gameEngine->GetLayersCount(); i++)
	{
		gameEngine->DeleteLayer(i);
	}
}