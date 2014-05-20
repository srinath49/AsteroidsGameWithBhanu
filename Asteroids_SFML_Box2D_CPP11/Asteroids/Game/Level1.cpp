
#include "Level1.h"

BigRock* bigRock2;
BigRock* bigRock3;

void Level1::CreateLayers()
{
	backgroundLayer = gameEngine->AddLayer();
	rocksLayer = gameEngine->AddLayer();
	playerLayer = gameEngine->AddLayer();
}

void Level1::CreateGameObjects()
{

	screenBackground = new Background("ScreenBackground" , gameEngine , false , false , Vector2(0.0f, 0.0f), "BG_Plain.png", false, 1, 1);

	player = new Player("Character", gameEngine, true, true, Vector2(0.0f, 0.0f), "spaceShip.png", true, 2, 2);
	player->SetTag("PlayerShip");
	player->currentLevel = this;

	bigRock1 = new BigRock("Character2", gameEngine, true, true, Vector2(4.0f , 1.0f), "BigRock1.png", false, 1, 1);
	bigRock1->medRockATexture = "MediumRock1_A.png";
	bigRock1->medRockBTexture = "MediumRock1_B.png";

	bigRock1->smallRock1ATexture = "SmallRock1_A1.png";
	bigRock1->smallRock2ATexture = "SmallRock1_A2.png";
	bigRock1->smallRock3ATexture = "SmallRock1_A3.png";
	
	bigRock1->smallRock1BTexture = "SmallRock1_B1.png";
	bigRock1->smallRock2BTexture = "SmallRock1_B2.png";
	bigRock1->smallRock3BTexture = "SmallRock1_B3.png";
}

void Level1::AddObjectsToLayers()
{
	
	//Adding Objects to Layers
	gameEngine->GetLayer(backgroundLayer)->AddObjectToLayer(screenBackground);
	gameEngine->GetLayer(playerLayer)->AddObjectToLayer(player);
	gameEngine->GetLayer(rocksLayer)->AddObjectToLayer(bigRock1);
	//gameEngine->GetLayer(rocksLayer)->AddObjectToLayer(bigRock2);
	//gameEngine->GetLayer(rocksLayer)->AddObjectToLayer(bigRock3);
	levelDone = false;
	
}

void Level1::LevelWon()
{
	levelDone = true;
	gameEngine->RequestNextLevelLoad();
}

void Level1::LevelLost()
{
	levelDone = true;
	//gameEngine->RequestNextLevelLoad();
}

void Level1::Update(unsigned long frameNumber)
{	
	if(enemiesCount == 0 && rocksCount == 0)
	{
		LevelWon();
	}
	if(levelDone)
	{
		return;
	}
}


void Level1::OnPointerPressed(Vector2 point)
{
	GameObject* obj = gameEngine->GetDynamicObjectAtPoint(point);
	if(obj != nullptr)
	{
		obj->OnPointerPressed(point);
	}
}

void Level1::OnPointerMoved(Vector2 point)
{
	GameObject* obj = gameEngine->GetDynamicObjectAtPoint(point);
	if(obj != nullptr)
	{
		obj->OnPointerMoved(point);
	}
}

void Level1::OnPointerReleased(Vector2 point)
{
	GameObject* obj = gameEngine->GetDynamicObjectAtPoint(point);
	if(obj != nullptr)
	{
		obj->OnPointerReleased(point);
	}
}

void Level1::OnKeyPressed(sf::Keyboard::Key key)
{
	if(player == nullptr)
	{
		return;
	}
	player->OnKeyPressed(key);
}

void Level1::OnKeyReleased(sf::Keyboard::Key key)
{
	if(player == nullptr)
	{
		return;
	}
	player->OnKeyReleased(key);
}

void Level1::PlayerNull()
{
	player = nullptr;
	LevelLost();
}