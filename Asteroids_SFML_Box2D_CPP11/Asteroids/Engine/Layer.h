#pragma once

#include "GameObject.h"
//#include "Controller.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <list>

using namespace std;

class GameObject;

class Layer
{
	public:
		Layer(int index);
		bool AddObjectToLayer(void * object);
		void RemoveObject(string objectName);
		GameObject * GetObjectByName(string objectName);
		void Render(sf::RenderWindow *renderer/*, sf::Time globalTime*/);
		void Destroy();
		void Update(unsigned long frameNumber);
		void AddRemoveObjects();
		int layerIndex;
		int objIndex;
		bool layerDeleted;

	private:
		typedef std::map<string, GameObject *> ObjectMap;
		ObjectMap m_objectByRef;
		std::list<string> m_deleteQueue;
		std::list<GameObject *> m_addQueue;
};