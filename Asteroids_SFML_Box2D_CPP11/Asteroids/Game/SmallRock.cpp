#include "SmallRock.h"

void SmallRock::BeginContact(GameObject* _Object)
{
	if(_Object->CompareTag("Player"))
	{
		
	}
	else if(_Object->CompareTag("Bullet"))
	{   
   		SetState(BlastState);
	}
	
}

void SmallRock::EndContact(GameObject*)
{

}

void SmallRock::Start()
{
	SetGravity(0.0f);
	//SetVelocity(0.0f,0.0f);
	SetTag("Rock");
	SetState(NormalState);
	IsTrigger(true);
	collisionBox->ApplyTorque(1.0f, true);
}

void SmallRock::Update(unsigned long frameNumber)
{
	switch(currentState)
	{
		case NormalState:
			CheckCoordinates();
			break;
		case BlastState:
			BlastRock();
			break;
	}
	/*
	float x = GetVelocity().x;
	float y = GetVelocity().y;
	printf("%f, %f", &x, &y);
	*/
}

string SmallRock::GetType()
{
	return "SmallRock";
}


void SmallRock::BlastRock()
{
	Destroy();
}