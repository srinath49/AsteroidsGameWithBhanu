#include "MenuScreenLevel.h"

bool levelWon = false;

void MenuScreenLevel::CreateLayers()
{
	backgroundLayer	= gameEngine->AddLayer();
}

void MenuScreenLevel::CreateGameObjects()
{
	//BackgroundLayer GameObjects
	screenBackground = new Background("ScreenBackground" , gameEngine , false , false , Vector2(0.0f, 0.0f), "BG_Rocks.png", false, 1, 1);
	screenMessage = new Background("screenMessage" , gameEngine , false , false , Vector2(0.0f, 0.0f), "EnterToStart.png", false, 1, 1);
}

void MenuScreenLevel::AddObjectsToLayers()
{
	//BackgroundLayer GameObjects
	gameEngine->GetLayer(backgroundLayer)->AddObjectToLayer(screenBackground);
	gameEngine->GetLayer(backgroundLayer)->AddObjectToLayer(screenMessage);
}

void MenuScreenLevel::LevelWon()
{
	gameEngine->RequestNextLevelLoad();
	//screenBackground->Destroy();
	//screenMessage->Destroy();
}

void MenuScreenLevel::LevelLost()
{
	//gameEngine->RequestLevelReload();
}

void MenuScreenLevel::Update(unsigned long frameNumber)
{
	if(levelWon)
	{
		LevelWon();
	}
}

void MenuScreenLevel::OnPointerPressed(Vector2 point)
{

}

void MenuScreenLevel::OnPointerMoved(Vector2 point)
{

}

void MenuScreenLevel::OnPointerReleased(Vector2 point)
{

}

void MenuScreenLevel::OnKeyPressed(sf::Keyboard::Key key)
{
	switch(key)
	{
		case sf::Keyboard::Return:		
			//LevelWon();
			levelWon = true;
			break;
		case sf::Keyboard::Escape:
			break;
	}
}

void MenuScreenLevel::OnKeyReleased(sf::Keyboard::Key key)
{
	
}
