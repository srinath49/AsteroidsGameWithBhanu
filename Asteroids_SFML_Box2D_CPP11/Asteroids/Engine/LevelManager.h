#pragma once
#include "Game/Game.h"
#include "GameObject.h"
#include <string>
#include "Level.h"

using namespace std;

class Game;
class Level;

class LevelManager
{
public:
	LevelManager(Game* _Main, int TotalLevels);
	
	bool LoadLevel(int LevelToLoad);
	bool ReloadLevel();
	void CreateLevel(Level* _NewLevel);
	void UnloadCurrentLevel();
	void Update(unsigned long frameNumber);
	Level* GetCurrentLevel();
	Level** Levels;

private:
	int TotalLevels;
	Game* gameLoop;
	bool* LevelsCreated;
	int CurrentLevel;
	int PreviousLevel;
};

