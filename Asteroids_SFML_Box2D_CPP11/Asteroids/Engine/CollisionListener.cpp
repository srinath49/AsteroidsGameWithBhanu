// Srinath
#include "GameObject.h"
#include "CollisionListener.h"

CollisionListener::CollisionListener(void)
{	
}


CollisionListener::~CollisionListener(void)
{
}

void CollisionListener::BeginContact(b2Contact* contact)
{
	GameObject* object1;
	GameObject* object2; 
	object1 = (GameObject*)contact->GetFixtureA()->GetBody()->GetUserData();
	object2 = (GameObject*)contact->GetFixtureB()->GetBody()->GetUserData();
	if(object1 != nullptr)
	{
		object1->BeginContact(object2);
	}
	if(object2 != nullptr)
	{
		object2->BeginContact(object1);
	}
} 