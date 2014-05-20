#include "Engine.h"
#include <assert.h>
#include <windows.h>
#include <sstream>
#include "CollisionListener.h"
#include "GameObject.h"
#include "Layer.h"
#include "TextureManager.h"

class b2World;

// Initialize Box2D Physics 
b2World* phyxWorld;
b2Fixture* fix;
b2Vec2 gravity(0.0f, -10.0f);
b2World myWorld(gravity);

Engine::Engine():
	layerCount(0),
	frameNumber(0)
{


}


void Engine::Initialize()
{
	// Initializing Box2D 
	phyxWorld = &myWorld;
	CollisionListener* gcl = new CollisionListener();
	phyxWorld->SetContactListener(gcl);
	
	textureManager = new TextureManager();

	frameChanged = false;

	//Initialise Game Window
	renderer = new sf::RenderWindow();
}


Layer * Engine::GetLayer(int layerId)
{
	if (layerId<layerCount)
	{
		return layers[layerId];
	}
	else
	{
		return NULL;
	}
}

void Engine::DeleteLayer(int layerId)
{
	if (layerId<layerCount)
	{
		layers[layerId]->Destroy();
		layers[layerId]->layerDeleted = true;
	}
}

int Engine::AddLayer()
{
	for (int i = 0; i < layerCount; i++) // Check for any empty layer positions in the array
	{
		if (layers[i] == nullptr) // True when a spot is empty, creates and adds a layer to that spot, returns index
		{
			Layer * layer = new Layer(i);
			layers[i] = layer;
			return i;
		}
	}

	 //No empty layer spots found, creating a new layer at the end of the array

	 Layer * layer = new Layer(layerCount);
	 layers[layerCount] = layer;
	 layerCount++;
	 return layerCount-1;
}

void Engine::Render(/*sf::Time globalTime*/)
{
	// Step the physics world
	phyxWorld->Step(1.0f/60.0f, 6, 2);

	// Start drawing 

	//Update Loop
	//Fire the update function on all gameobjects
	for(int i=0; i<layerCount; i++)
	{
		if (layers[i]!=nullptr)
		{
			layers[i]->Update(frameNumber);
		}
	}

	Update(++frameNumber);
	//Render Loop
	//This will loop through all the layers and update them
	for(int i=0; i<layerCount; i++)
	{
		if (layers[i]!=nullptr)
		{
			layers[i]->Render(renderer/*, globalTime*/);
		}
	}

	//Cull Loop
	//This loop will remove any objects which are flagged for deletion
	for(int i=0; i<layerCount; i++)
	{
		if (layers[i]!=nullptr)
		{
			layers[i]->AddRemoveObjects();
			if (layers[i]->layerDeleted)
			{
				//delete(m_Layers[i]);
				for(int x=i+1; x<layerCount; x++)
				{
					layers[x-1] = layers[x];
				}
				layerCount--;
				layers[i] = nullptr;
			}
		}
	}
   
}

GameObject* Engine::GetDynamicObjectAtPoint(Vector2 _Point)
{
	// Make a small box where the point is
	GameObject *tempObj = nullptr;
	
	tempBody.lowerBound.Set(_Point.x - 0.001f, _Point.y - 0.001f);
	tempBody.upperBound.Set(_Point.x + 0.001f, _Point.y + 0.001f);

	myWorld.QueryAABB(&queryCallback, tempBody);
	
	for (unsigned int i = 0; i < queryCallback.foundBodies.size(); i++) 
	{
		if(queryCallback.foundBodies[i]->GetUserData() != nullptr)
		{
			tempObj = (GameObject*)queryCallback.foundBodies[i]->GetUserData();
			if(tempObj->IsDynamic())
			{
				queryCallback.foundBodies.clear();
				return tempObj;
			}
		}	
	}
	
  return nullptr;
}

GameObject* Engine::GetStaticObjectAtPoint(Vector2 _Point)
{
	// Make a small box where the point is
	GameObject *tempObj = nullptr;
	
	tempBody.lowerBound.Set(_Point.x - 0.001f, _Point.y - 0.001f);
	tempBody.upperBound.Set(_Point.x + 0.001f, _Point.y + 0.001f);

	myWorld.QueryAABB(&queryCallback, tempBody);

	
  for (unsigned int i = 0; i < queryCallback.foundBodies.size(); i++) 
  {
	  if(queryCallback.foundBodies[i]->GetUserData() != nullptr)
	  {
		 tempObj = (GameObject*)queryCallback.foundBodies[i]->GetUserData();
		 if(!tempObj->IsDynamic())
		 {
			 queryCallback.foundBodies.clear();
			 return tempObj;
		 }
	  }
	
  }
  
  return nullptr;
}

GameObject* Engine::GetObjectAtPoint(Vector2 _Point)
{
	// Make a small box where the point is
	GameObject *tempObj = nullptr;

	tempBody.lowerBound.Set(_Point.x - 0.0075f, _Point.y - 0.0075f); // Previous value of 0.001f was too small. So changed it to 0.0075f
	tempBody.upperBound.Set(_Point.x + 0.0075f, _Point.y + 0.0075f); // Previous value of 0.001f was too small. So changed it to 0.0075f

	myWorld.QueryAABB(&queryCallback, tempBody);
	
	int index = queryCallback.foundBodies.size();			// Total bodies found
	GameObject** foundObjects =  new GameObject*[index];	// Array to store bodies found
	int foundObjectsIndex = -1;								// Index of the above array for safe iteration purposes

	for (int i = 0; i < index; i++) 
	{
		if(queryCallback.foundBodies[i]->GetUserData() != nullptr)
		{
			tempObj = (GameObject*)queryCallback.foundBodies[i]->GetUserData();
			if(tempObj)
			{
				foundObjects[++foundObjectsIndex] = tempObj;	// Previousle we just returned bob. This was eturning te first object found irrespective of the layers. So now we store all objects found
			}
		}
	}

	queryCallback.foundBodies.clear();

	// If any object was found, we do a simple bubble sort n them to find the object with the highest layer.
	// Having a loop to collect all the bodies, and then another multi-layered loop for sortin seems to me as a bit inefficient.
	// Unfortunately I cannot think of a better way, perhaps an insertion sort might be an answer.
	// Having said that usually we do not find more than 4-5 bodies on eac click; so, maybe its just fine.
	// If its not fine, then please fix this, and apply this or the corrected method to the other two functions GetStaticBodyAtPoint() and GetDynamicBodyAtPoint().
	if(foundObjectsIndex >=0)
	{
		bool sorted = true;   
		GameObject* tempObj2;
		for(int outerIndex = 1; ((outerIndex <= foundObjectsIndex) && sorted); outerIndex++)
		{
			sorted = false;
			for (int innerIndex=0; innerIndex < (foundObjectsIndex -1); innerIndex++)
			{
				if (foundObjects[innerIndex]->GetMyLayer() < foundObjects[innerIndex+1]->GetMyLayer())		// Check if the current element is greater than the next element in the array. If so Swap the emements!
				{ 
					tempObj2 = foundObjects[innerIndex];							// swap the elements of the array
					foundObjects[innerIndex] = foundObjects[innerIndex+1];
					foundObjects[innerIndex+1] = tempObj2;
					sorted = true;										// Set sorted to true to indicate that a swap occurred.
				}
			}
		}
		return foundObjects[0];
	}
	
  return nullptr;
}

// Convert directional vector to angel
float Engine::ConvertDirectionVectorToAngle(Vector2* _Direction)
{
	
	float _Angle = atan2(_Direction->x,_Direction->y);
	// 1 radian = 57.2957795 degrees
	_Angle *=  57.2957795f;

	if(_Angle<0)
	{
		_Angle = 360 + _Angle;
	}
	return (_Angle);

}

// Convert angle to a directional vector
Vector2 Engine::ConvertDirectionAngleToVector(float _Angle)
{
	// 1 degree = 0.0174532925 radians
	Vector2* tempPos =  new Vector2(sin(_Angle*0.0174532925f),cos(_Angle*0.0174532925f));
	return (*tempPos);
}

float Engine::GetDistance(Vector2 Point1, Vector2 Point2)
{
	float p1 = (Point2.x-Point1.x);
	p1*=p1;
	float p2 = (Point2.y-Point1.y);
	p2*=p2;
	return sqrtf((p1)+(p2));
}