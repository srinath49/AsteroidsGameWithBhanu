#include "Layer.h"
#include <sstream>

Layer::Layer(int index)
	: objIndex(0),
	  layerIndex(index),
	  layerDeleted(false)
{
}

bool Layer::AddObjectToLayer(void * object)
{
	GameObject * nGo = (GameObject *)object;
	m_addQueue.push_back(nGo);
	return true;
}

GameObject * Layer::GetObjectByName(string name)
{
	auto it = m_objectByRef.find(name);
	if (it == m_objectByRef.end())
    {
        return NULL;
    }
	return m_objectByRef[name];
}

void Layer::RemoveObject(string objectName)
{
	GameObject * n = GetObjectByName(objectName);
	if (n!=NULL)
	{
		m_deleteQueue.push_back(objectName);
	}
}

void Layer::Destroy()
{
	typedef std::map<string, GameObject *>::iterator it_type;
	for(it_type iterator = m_objectByRef.begin(); iterator != m_objectByRef.end(); iterator++) 
	{
		RemoveObject(iterator->first);
	}
}

void Layer::Update(unsigned long frameNumber)
{
	typedef std::map<string, GameObject *>::iterator it_type;
	for(it_type iterator = m_objectByRef.begin(); iterator != m_objectByRef.end(); iterator++) 
	{
		iterator->second->Update(frameNumber);
		//iterator->second->SetTextureFrame(frameNumber);
	}
}

void Layer::Render(sf::RenderWindow* renderer/*, sf::Time globalTime*/)
{
	typedef std::map<string, GameObject *>::iterator it_type;
	for(it_type iterator = m_objectByRef.begin(); iterator != m_objectByRef.end(); iterator++) 
	{
		iterator->second->Render(renderer/*, globalTime*/);
	}
}

void Layer::AddRemoveObjects()
{
	
	for(std::list<string>::iterator iterator = m_deleteQueue.begin(); iterator != m_deleteQueue.end(); iterator++) 
	{
		GameObject * n = GetObjectByName(*iterator);
		if (n!=NULL)
		{
			m_objectByRef.erase(*iterator);
			n->OnDestroy();
			delete(n);
		}
	}
	m_deleteQueue.clear();
	

	for(std::list<GameObject *>::iterator iterator = m_addQueue.begin(); iterator != m_addQueue.end(); iterator++) 
	{
		GameObject * nGo = *iterator;
		nGo->layer=layerIndex;
		nGo->isActive = true;
		string objectName = nGo->GetName();
		string appendString = "";

		int append = 0;
		bool insertOk = false;

		while(!insertOk)
		{
			string tmp = objectName + appendString;
			nGo->SetName(tmp);
			std::pair<ObjectMap::iterator, bool> res = m_objectByRef.insert(pair<string, GameObject*>(tmp,nGo));
			if ( ! res.second ) 
			{
				if (m_objectByRef[tmp] == nGo)
				{
					insertOk = true;
				}
				else
				{
					append++;
					stringstream streamVal;
					streamVal << append;
					appendString = streamVal.str();
					int h = 4;
				}
			}
			else
			{
				insertOk = true;
			}
		}
		nGo->Start();
	}
	m_addQueue.clear();
}