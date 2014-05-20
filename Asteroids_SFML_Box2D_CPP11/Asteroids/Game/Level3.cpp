#include "Level3.h"

void Level3::CreateLayers()
{
	backgroundLayer = gameEngine->AddLayer();
	rocksLayer = gameEngine->AddLayer();
	playerLayer = gameEngine->AddLayer();
}

void Level3::CreateGameObjects()
{

	screenBackground = new Background("ScreenBackground" , gameEngine , false , false , Vector2(0.0f, 0.0f), "BG_Plain.png", false, 1, 1);

	player = new Player("Character", gameEngine, true, true, Vector2(0.0f, 0.0f), "spaceShip.png", true, 2, 2);
	player->SetTag("PlayerShip");
	player->currentLevel = this;

	bigRock1 = new BigRock("Character2", gameEngine, true, true, Vector2(4.0f , 1.0f), "BigRock1.png", false, 1, 1);
	bigRock1->currentLevel = this;

	bigRock1->medRockATexture = "MediumRock1_A.png";
	bigRock1->medRockBTexture = "MediumRock1_B.png";

	bigRock1->smallRock1ATexture = "SmallRock1_A1.png";
	bigRock1->smallRock2ATexture = "SmallRock1_A2.png";
	bigRock1->smallRock3ATexture = "SmallRock1_A3.png";
	
	bigRock1->smallRock1BTexture = "SmallRock1_B1.png";
	bigRock1->smallRock2BTexture = "SmallRock1_B2.png";
	bigRock1->smallRock3BTexture = "SmallRock1_B3.png";

	bigRock2 = new BigRock("Character3", gameEngine, true, true, Vector2(8.0f , 1.0f), "BigRock2.png", false, 1, 1);
	bigRock2->currentLevel = this;

	bigRock2->medRockATexture = "MediumRock2_A.png";
	bigRock2->medRockBTexture = "MediumRock2_B.png";

	bigRock2->smallRock1ATexture = "SmallRock2_A1.png";
	bigRock2->smallRock2ATexture = "SmallRock2_A2.png";
	bigRock2->smallRock3ATexture = "SmallRock2_A3.png";
	
	bigRock2->smallRock1BTexture = "SmallRock2_B1.png";
	bigRock2->smallRock2BTexture = "SmallRock2_B2.png";
	bigRock2->smallRock3BTexture = "SmallRock2_B3.png";

	bigRock3 = new BigRock("Character4", gameEngine, true, true, Vector2(12.0f , 1.0f), "BigRock3.png", false, 1, 1);
	bigRock3->currentLevel = this;

	bigRock3->medRockATexture = "MediumRock3_A.png";
	bigRock3->medRockBTexture = "MediumRock3_B.png";

	bigRock3->smallRock1ATexture = "SmallRock3_A1.png";
	bigRock3->smallRock2ATexture = "SmallRock3_A2.png";
	bigRock3->smallRock3ATexture = "SmallRock3_A3.png";
	
	bigRock3->smallRock1BTexture = "SmallRock3_B1.png";
	bigRock3->smallRock2BTexture = "SmallRock3_B2.png";
	bigRock3->smallRock3BTexture = "SmallRock3_B3.png";
}

void Level3::AddObjectsToLayers()
{
	
	//Adding Objects to Layers
	gameEngine->GetLayer(backgroundLayer)->AddObjectToLayer(screenBackground);
	gameEngine->GetLayer(playerLayer)->AddObjectToLayer(player);
	gameEngine->GetLayer(rocksLayer)->AddObjectToLayer(bigRock1);
	gameEngine->GetLayer(rocksLayer)->AddObjectToLayer(bigRock2);
	gameEngine->GetLayer(rocksLayer)->AddObjectToLayer(bigRock3);
	levelDone = false;

	if(music.openFromFile("Assets/Lazer.aif"))
	{
		music.play();
	}
	
}

void Level3::LevelWon()
{
	levelDone = true;
	gameEngine->RequestNextLevelLoad();
}

void Level3::LevelLost()
{
	levelDone = true;
	//gameEngine->RequestNextLevelLoad();
}

void Level3::Update(unsigned long frameNumber)
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

void Level3::OnPointerPressed(Vector2 point)
{
	GameObject* obj = gameEngine->GetDynamicObjectAtPoint(point);
	if(obj != nullptr)
	{
		obj->OnPointerPressed(point);
	}
}

void Level3::OnPointerMoved(Vector2 point)
{
	if(player != nullptr)
	{
		player->OnPointerMoved(point);
	}
}

void Level3::OnPointerReleased(Vector2 point)
{
	GameObject* obj = gameEngine->GetDynamicObjectAtPoint(point);
	if(obj != nullptr)
	{
		obj->OnPointerReleased(point);
	}
}

void Level3::OnKeyPressed(sf::Keyboard::Key key)
{
	if(player == nullptr)
	{
		return;
	}
	player->OnKeyPressed(key);
}

void Level3::OnKeyReleased(sf::Keyboard::Key key)
{
	if(player == nullptr)
	{
		return;
	}
	player->OnKeyReleased(key);
}

void Level3::PlayerNull()
{
	player = nullptr;
	LevelLost();
}