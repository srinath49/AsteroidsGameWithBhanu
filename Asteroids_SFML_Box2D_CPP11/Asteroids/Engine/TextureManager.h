#pragma once
#include "Engine.h"
#include "Texture.h"
#include <string>
#include <unordered_map>

class Engine;

struct TextureEntry
{
	Texture * texture;
	int refCount;
	string textureName;
};

class TextureManager
{
	public:
		TextureEntry * AddTexture(Engine * engineRef, string textureName, bool isSprite, int rows, int columns);
		std::unordered_map <string, TextureEntry *> textureStore;
		void DeleteTexture(string textureName);
};