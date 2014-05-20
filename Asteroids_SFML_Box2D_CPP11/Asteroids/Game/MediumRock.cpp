#include "MediumRock.h"
#include "SmallRock.h"

void MediumRock::BeginContact(GameObject* _Object)
{
	if(_Object->CompareTag("Player"))
	{
		
	}
	else if(_Object->CompareTag("Bullet"))
	{   
   		SetState(BlastState);
	}
	
}

void MediumRock::EndContact(GameObject*)
{

}

void MediumRock::Start()
{
	SetGravity(0.0f);
	//SetVelocity(0.0f,0.0f);
	SetTag("Rock");
	SetState(NormalState);
	IsTrigger(true);
	collisionBox->ApplyTorque(1.0f, true);
}

void MediumRock::Update(unsigned long frameNumber)
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

string MediumRock::GetType()
{
	return "MediumRock";
}

void MediumRock::BlastRock()
{
	SmallRock* rock1 = new SmallRock("SmallRockA", gameEngine, true, true, Vector2(position.x+1.5f, position.y+1.5f), smallRock1Texture, false, 1, 1);
	SmallRock* rock2 = new SmallRock("SmallRockB", gameEngine, true, true, Vector2(position.x-1.5f, position.y-1.5f), smallRock2Texture, false, 1, 1);
	SmallRock* rock3 = new SmallRock("SmallRockC", gameEngine, true, true, Vector2(position.x-1.5f, position.y-1.5f), smallRock3Texture, false, 1, 1);

	Vector2 vel1;
	Vector2 vel2;
	Vector2 vel3;
	
	vel1 = this->GetVelocity();
	vel2 = this->GetVelocity();
	vel3 = this->GetVelocity();
	
	if (vel1.x <0.0f)
	{
		vel1.x -= 1.5f;
	}
	else
	{
		vel1.x += 1.5f;
	}

	if(vel1.y < 0.0f)
	{
		vel1.y -= 1.5f;
	}
	else
	{
		vel1.y += 1.5f;
	}

	if (vel2.x <0.0f)
	{
		vel2.x -= 1.5f;
	}
	else
	{
		vel2.x += 1.5f;
	}

	if(vel2.y < 0.0f)
	{
		vel2.y -= 1.5f;
	}
	else
	{
		vel2.y += 1.5f;
	}

	if (vel3.x <0.0f)
	{
		vel3.x -= 1.5f;
	}
	else
	{
		vel3.x += 1.5f;
	}

	if(vel3.y < 0.0f)
	{
		vel3.y -= 1.5f;
	}
	else
	{
		vel3.y += 1.5f;
	}

	rock1->SetVelocity(vel1.x, vel1.y);
	rock2->SetVelocity(-vel2.x, -vel2.y);
	rock2->SetVelocity(-vel3.x, vel3.y);

	gameEngine->GetLayer(2)->AddObjectToLayer(rock1);
	gameEngine->GetLayer(2)->AddObjectToLayer(rock2);
	gameEngine->GetLayer(2)->AddObjectToLayer(rock3);

	Destroy();
}