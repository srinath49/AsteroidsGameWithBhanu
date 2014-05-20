#include <stdio.h>
#include "Engine/Engine.h"
#include "Game/Game.h"
#include <thread>

sf::RenderWindow* rWin;
Game* gameEngine;

bool leftKey, rightKey, upKey, downKey, spaceKey, returnKey;

sf::Keyboard::Key* key = new sf::Keyboard::Key();

void keyPressedThread(sf::Keyboard::Key* key)
{
	if(*key != sf::Keyboard::Unknown)
	{
		gameEngine->OnKeyPressed(*key);
	}
}

void keyReleasedThread(sf::Keyboard::Key* key)
{
	if(*key != sf::Keyboard::Unknown)
	{
		gameEngine->OnKeyReleased(*key);
	}
}

void keyPressed(sf::Keyboard::Key* key)
{
	if(*key != sf::Keyboard::Unknown)
	{
		gameEngine->OnKeyPressed(*key);
	}
}

void keyReleased(sf::Keyboard::Key* key)
{
	if(*key != sf::Keyboard::Unknown)
	{
		gameEngine->OnKeyReleased(*key);
	}
}


void keyPress(sf::Keyboard::Key* key)
{
	switch (*key)
	{
	case sf::Keyboard::Left:
		leftKey = true;
		break;
	case sf::Keyboard::Right:
		rightKey = true;
		break;
	case sf::Keyboard::Up:
		upKey = true;
		break;
	case sf::Keyboard::Down:
		downKey = true;
		break;
	case sf::Keyboard::Space:
		spaceKey = true;
		break;
	case sf::Keyboard::Return:
		returnKey = true;
		break;
	default:
		break;
	}
}

void keyRelease(sf::Keyboard::Key* key)
{
	switch (*key)
	{
	case sf::Keyboard::Left:
		leftKey = false;
		break;
	case sf::Keyboard::Right:
		rightKey = false;
		break;
	case sf::Keyboard::Up:
		upKey = false;
		break;
	case sf::Keyboard::Down:
		downKey = false;
		break;
	case sf::Keyboard::Space:
		spaceKey = false;
		break;
	case sf::Keyboard::Return:
		returnKey = false;
	default:
		break;
	}
	keyReleased(key);
}

int main(int argc, char** argv)
{
	sf::Keyboard::Key* key = new sf::Keyboard::Key;
	sf::Keyboard::Key tempKey = sf::Keyboard::Unknown;
	key = &tempKey;

	// Create Input Handler Threads
	/*
	std::thread onKeyPressed(&keyPressed, key);
	std::thread onKeyReleased(&keyReleased, key);
	*/
	sf::Thread onKeyPressed(&keyPressedThread, key);
	sf::Thread onKeyReleased(&keyReleasedThread, key);

	// Create Game Engine Instance
	gameEngine = new Game();

	//Initialise Game Engine
	gameEngine->Initialize();

	rWin = gameEngine->GetRenderer();

	//Create Game Window
	rWin->create(sf::VideoMode(800, 600), "Game Window");
	rWin->setFramerateLimit(60);

	//Start Game Engine
	gameEngine->Start();
	
	sf::Clock globalClock;
	sf::Time globalTime;
	globalTime = globalClock.restart();
	// Game Loop
	while(rWin->isOpen())
	{
		sf::Event event;
        while (rWin->pollEvent(event))
        {
			switch(event.type)
			{
				
				case sf::Event::KeyPressed:
					//gameEngine->OnKeyPressed(event.key.code);
					*key = event.key.code;
					//onKeyPressed.launch();
					keyPress(key);
					break;
				
				case sf::Event::KeyReleased:
					//gameEngine->OnKeyReleased(event.key.code);
					*key = event.key.code;
					//onKeyReleased.launch();
					keyRelease(key);
					break;
				/*	
				case sf::Event::MouseMoved:
					gameEngine->OnPointerReleased(Vector2(sf::Mouse::getPosition().x*1.0f, sf::Mouse::getPosition().y*1.0f));
					break;

				case sf::Event::MouseButtonPressed:
					gameEngine->OnPointerReleased(Vector2(sf::Mouse::getPosition().x*1.0f, sf::Mouse::getPosition().y*1.0f));
					break;

				case sf::Event::MouseButtonReleased:
					gameEngine->OnPointerReleased(Vector2(sf::Mouse::getPosition().x*1.0f, sf::Mouse::getPosition().y*1.0f));
					break;
				*/
				case sf::Event::Closed:
					rWin->close();
					return 0;
			}
		}
		

		if(returnKey)
		{
			*key = sf::Keyboard::Return;
			keyPressed(key);
		}
		else if(spaceKey)
		{
			*key = sf::Keyboard::Space;
			keyPressed(key);
		}
		else
		{
			if(leftKey)
			{
				*key = sf::Keyboard::Left;
				//onKeyPressed.join();
				onKeyPressed.launch();
			}
			if(rightKey)
			{
				*key = sf::Keyboard::Right;
				//onKeyPressed.join();
				onKeyPressed.launch();
			}
			if(upKey)
			{
				*key = sf::Keyboard::Up;
				//onKeyPressed.join();
				onKeyPressed.launch();
			}
			if(downKey)
			{
				*key = sf::Keyboard::Down;
				//onKeyPressed.join();
				onKeyPressed.launch();
			}
		}


		//Clear the window with black color
		rWin->clear(sf::Color::Black);
		//Render all Game Objects
		globalTime = globalClock.getElapsedTime();
		gameEngine->Render(/*globalTime*/);
		//Display to Screen
		rWin->display();
		float frames = globalTime.asSeconds();
		if(frames > 6.0f)
		{
			globalTime = globalClock.restart();
		}
		/*
		clock.restart();
		sf::Time elapsed = clock.getElapsedTime();
		while( ( (elapsed.asSeconds()) <= 1.0f/45) )
		{
			elapsed = clock.getElapsedTime();
		}
		*/
        
	}

	return 0;
}