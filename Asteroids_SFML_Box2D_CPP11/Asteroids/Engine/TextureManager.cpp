#include "TextureManager.h"

TextureEntry * TextureManager::AddTexture(Engine * engineRef, string textureName, bool isSprite, int rows, int columns)
{	
	string fileName = "Assets/";

	fileName += textureName;
	TextureEntry * tex = TextureManager::textureStore[textureName];

	Texture* tempTexture = new Texture();
		
	// Set Texture numbers of rows
	tempTexture->rows = rows;
	// Set texture number of colums
	tempTexture->columns = columns;
	// Set texture name
	tempTexture->textureName = textureName;
	// Set texture sprite 
	tempTexture->isSprite = isSprite;
	TextureEntry * texEnt = new TextureEntry();

	// Set texture bitmap
	/*if (tex == NULL)
	{*/	
		TextureEntry * texEnt2 = new TextureEntry();
		Texture* tempTexture2 = new Texture();
		tempTexture2->image->loadFromFile(fileName);
		tempTexture->image = tempTexture2->image;
		texEnt2->textureID=++textureID;
		// Set width and of the texture
		tempTexture->SetSize();
		// Set the time animation play time
		tempTexture->frameSpeed = 10.0f;
		texEnt->texture = tempTexture;
		texEnt->textureName = textureName;
		texEnt2->texture = tempTexture2;
		texEnt2->textureName = textureName;
		TextureManager::textureStore[textureName] = texEnt2;
	/*}
	else
	{
		tempTexture=tex->texture;
		tex->refCount=tex->refCount+1;
			// Set width and of the texture
		tempTexture->SetSize();
		// Set the time animation play time
		tempTexture->frameSpeed = 10.0f;
		texEnt->texture = tempTexture;
		texEnt->textureName = textureName;
	}*/

	return texEnt;

}
void TextureManager::DeleteTexture(string texName, int textureID)
{
	//TODO Tom have a look at this, ive moved te out of the if(te->refCount==0) as its not all a referance now, but deleting that deletes te->texture that is one
	//I cant think of a way round this atm
	
	TextureEntry * texEnt = TextureManager::textureStore[texName];

	
	if (texEnt != NULL)
	{
		//texEnt->refCount--;
		if (texEnt->textureID==textureID)
		{
			//textureStore.erase(texName);
			texEnt->texture->~Texture();
			delete texEnt->texture;
			delete texEnt;
		}
	}
}