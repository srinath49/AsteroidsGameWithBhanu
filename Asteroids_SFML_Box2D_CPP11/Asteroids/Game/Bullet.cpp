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

	lifeClock.restart();
	AddForce(0.0f, 150.0f, Coordinate::Local);
}

void Bullet::Update(unsigned long frameNumber)
{
	if(destroy)
	{
		Destroy();
		destroy = false;
		return;
	}
	if(GetVelocitySize() < 80.0f)
	{
		AddForce(0.0f, 50.0f, Coordinate::Local);
		//SetRotation(GetRotationAngle());
		//SetVelocity(GetVelocity().x, 8.0f);
	}
	if(lifeClock.getElapsedTime().asSeconds() > 3.0f)
	{
		destroy = true;
	}
}
