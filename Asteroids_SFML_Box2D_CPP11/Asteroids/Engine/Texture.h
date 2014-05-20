#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "AnimatedSprite.hpp"

using namespace std;

class GameObject;

class Texture
{
private:
	int currentColumn;
	
	int currentRow;

	float frameStartTime;
	float nextFrameTime;

	bool nextFrame;
	bool pause;

public:
	int textureID;
	int rows;
	int columns;
	int currentFrame;
	int numOfFrames;

	float width;
	float height;
	float frameRight;
	float frameLeft;
	float frameTop;
	float frameBottom;
	float frameSpeed;
	bool isSprite;
	
	GameObject* owner;

	sf::Texture* image;
	sf::Sprite* sprite;
	string textureName;

	sf::Time timer;
	sf::Clock clock;

	//sf::RenderTarget* renderer;

	void SetSize();
	void PlaySprite(/*Animation anim*/);
	void PauseSprite();
	void ResumeSprite();
	bool IsPlaying();
	void SetFrameSpeed(float speed);
	void SetTextureFrame(int frameNumber);
	Texture();
};

