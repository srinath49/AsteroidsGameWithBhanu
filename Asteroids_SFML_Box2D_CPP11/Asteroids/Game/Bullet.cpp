#include "Bullet.h"
#include "AsteroidRock.h"

void Bullet::BeginContact(GameObject* object)
{
	if(object->CompareTag("Rock"))
	{
		destroy = true;
	}
	else if(object->CompareTag("Enemy"))
	{
		destroy = true;
	}
	
}

void Bullet::EndContact(GameObject* object)
{

}

void Bullet::Start()
{
	SetGravity(0.0f);
	SetVelocity(0.0f,0.0f);
	SetFriction(0.001f);
	destroy = false;
	IsTrigger(true);
	SetTag("Bullet");
}

void Bullet::Update(unsigned long frameNumber)
{
	if(destroy)
	{
		Destroy();
	}
	if(GetVelocitySize() < 8.0f)
	{
		AddForce(0.0f, 15.0f, Coordinate::Local);
	}
}
