#pragma once

//#include "Controller.h"
#include <string>
#include "Box2D.h"
#include <SFML/Graphics.hpp>
#include "BasicMath.h"
#include "MyQueryCallback.h"

class GameObject;
class Layer;
class TextureManager;

using namespace std;

/**
 * The Engine class is the mid-level game loop that handles the creation of all the game elements like the layers, gameobjects, etc.
 * The users however will NOT be using the Engine class directly. Instead, they will be using the Subclass of the Engine class -> the Game class.
 * In the Game, the users can add their game specific member variables and member functions. The Engine class how ever is the background class that handles the creation 
 * and deletion of all the game elements based on the requirements, amongst other things like the integration of the Box2D physics engine, etc.
 */
class Engine
{

private:

	b2AABB tempBody;
	unsigned long frameNumber;		/** The current frame */

	struct KeyStuct
	{
		bool thisUpdate;
		bool lastUpdate;
		//Windows::System::VirtualKey KeyID;
	};

	typedef std::map<std::string,KeyStuct> KeyMap;
	KeyMap m_Key;
	MyQueryCallback queryCallback;

protected:
	sf::RenderWindow* renderer;
	
	b2Body*			 phyxBody;
	b2Fixture*		 phyxFix;

	int layerCount;	/** Total number of layers */
	Layer* layers[20];/** Layers Array */

	bool frameChanged;
	unsigned long int prevFrame;
	unsigned long int currentFrame;

public:

	TextureManager * textureManager;

	/**
	 * Initializes the Engine class. Sets references to the Direct2d Device, Direct2D Device Context, creates the Engine camera, TextureManager, AudioManager, Physics world etc.
	 */
	void Initialize();	

	/**
	 * Renders all the existing GameObjects to the screen
	 */
	void Render(/*sf::Time globalTime*/);

	//Default Constructor
	Engine();

	/**
	 * Returns a reference to the render window
	 * 
	 * @return	renderer	The SFML RenderWindow object reference
	 */
	sf::RenderWindow* GetRenderer(){return renderer;}

	/**
	 * Adds a New Layer to the game and gives the current count of the layers
	 *
	 * @return		The total number of Layers in the game
	 */
	int AddLayer();

	/**
	 * Deletes a Layer from the game
	 *
	 * @param			layerId			The ID of the layer to delete from the world
	 */
	void DeleteLayer(int layerId);

	/**
	 * Gets the layer with the specified ID
	 *
	 * @return		The Layer with ID =  layerId
	 */
	Layer * GetLayer(int layerId);

	/**
	 * Gets the total layers in the game
	 *
	 * @return		The Layers Count 
	 */
	int GetLayersCount();

	/**
	 * Gets the dynamic gameobject at the specified point
	 *
	 * @param		_Point		The point to check for dynamic body
	 * @return		A GameObject at the given point if it is a dynamic body. If no dynamic GameObject is found at point, then it returns nullptr
	 */
	GameObject* GetDynamicObjectAtPoint(Vector2 _Point);

	/**
	 * Gets the gameobject at the specified point
	 *
	 * @param		_Point		The point to check for game object
	 * @return		A GameObject at the given point. If no GameObject is found at point, then it returns nullptr
	 */
	GameObject* GetObjectAtPoint(Vector2 _Point);

	/**
	 * Gets the static gameobject at the specified point
	 *
	 * @param		_Point		The point to check for static body
	 * @return		A GameObject at the given point if it is a static body. If no static GameObject is found at point, then it returns nullptr
	 */
	GameObject* GetStaticObjectAtPoint(Vector2 _Point);

	/**
	 * A virtual function to be implemented by the Engine class's sub-class -> Game
	 * It is called by the Engine on the Game object, when it is created
	 */
	virtual void Start(){};

	/**
	 * A virtual function to be implemented by the Engine class's sub-class -> Game
	 * It is called by the Engine on the Game object each frame
	 */
	virtual void Update(unsigned long frameNumber){};


	/**
	 * Converts a Directional Vector into an Angle
	 *
	 * @return		Angle of the specified Directional Vector
	 */
	float ConvertDirectionVectorToAngle(Vector2* _Direction);

	/**
	 * Converts an Angle to a Directional vector
	 *
	 * @return		Directional Vector of the specified Angle
	 */
	Vector2 ConvertDirectionAngleToVector(float _Angle);

	/**
	 * Finds the distance between 2 Vector2 points
	 *
	 * @param	point1		The first point
	 * @param	point2		The second point
	 */
	float GetDistance(Vector2 point1, Vector2 point2);
};

