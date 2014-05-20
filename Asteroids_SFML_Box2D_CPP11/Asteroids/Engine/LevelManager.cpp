#include "LevelManager.h"
#include "Level.h"

LevelManager::LevelManager(Game* _Main, int _TotalLevels)
{
	TotalLevels = _TotalLevels;
	gameLoop = _Main;
	Levels = new Level*[TotalLevels];
	LevelsCreated = new bool[TotalLevels];
	for(int i =0; i< TotalLevels; i++)
	{
		LevelsCreated[i] = false;
	}
	CurrentLevel = -1;
	PreviousLevel = -1;
}

bool LevelManager::LoadLevel(int LevelToLoad)
{
	if(LevelToLoad < TotalLevels)
	{
		if(LevelsCreated[LevelToLoad])
		{
			Levels[LevelToLoad]->SetLevelState(LevelState::LevelLoading);
			Levels[LevelToLoad]->Initialize();
			PreviousLevel = CurrentLevel;
			CurrentLevel = LevelToLoad;
			Levels[LevelToLoad]->SetLevelState(LevelState::LevelLoaded);
			return true;
		}
	}
	return false;
}

bool LevelManager::ReloadLevel()
{
	if(CurrentLevel == -1)
	{
		return false;
	}
	return LoadLevel(CurrentLevel);
}

void LevelManager::CreateLevel(Level* newLevel)
{
	if(newLevel != nullptr && newLevel->levelNumber < TotalLevels)
	{
		if(LevelsCreated[newLevel->levelNumber])
		{
			Levels[newLevel->levelNumber]->ReleaseAllResources();
			LevelsCreated[newLevel->levelNumber] = false;
		}
		Levels[newLevel->levelNumber] = newLevel;
		LevelsCreated[newLevel->levelNumber] = true;
	}
}

void LevelManager::UnloadCurrentLevel()
{
	if(CurrentLevel == -1)
	{
		return;
	}
	Levels[CurrentLevel]->ReleaseAllResources();
}

void LevelManager::Update(unsigned long frameNumber)
{
	if(CurrentLevel == -1)
	{
		return;
	}
	Levels[CurrentLevel]->Update(frameNumber);
}

Level* LevelManager::GetCurrentLevel()
{
	return Levels[CurrentLevel];
}