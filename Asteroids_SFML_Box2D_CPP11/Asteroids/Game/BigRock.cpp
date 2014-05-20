#include "BigRock.h"
#include "MediumRock.h"
#include <math.h>

void BigRock::BeginContact(GameObject* _Object)
{
	if(_Object->CompareTag("Player"))
	{
		int x = 1;
	}
	else if(_Object->CompareTag("Bullet"))
	{   
   		SetState(BlastState);
	}
	
}

void BigRock::EndContact(GameObject*)
{

}

void BigRock::Start()
{
	SetGravity(0.0f);
	SetTag("Rock");
	float xVel = RandFloatInRange(-0.5f, 0.5f);
	float yVel = RandFloatInRange(-0.5f, 0.5f);
	SetVelocity(xVel, yVel);
	//this->collisionBox->ApplyTorque(RandFloatInRange(0.5f, 1.5f), true);
	SetState(NormalState);
	IsTrigger(true);
	collisionBox->ApplyTorque(1.0f, true);
}

void BigRock::Update(unsigned long frameNumber)
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

string BigRock::GetType()
{
	return "BigRock";
}

void BigRock::BlastRock()
{
   	MediumRock* rock1 = new MediumRock("MediumRockA", gameEngine, true, true, Vector2(position.x+0.05f, position.y+0.05f), medRockATexture, false, 1, 1);
	MediumRock* rock2 = new MediumRock("MediumRockB", gameEngine, true, true, Vector2(position.x-0.05f, position.y-0.05f), medRockBTexture, false, 1, 1);

	rock1->currentLevel = currentLevel;
	rock2->currentLevel = currentLevel;

	currentLevel->rocksCount++;
	currentLevel->rocksCount++;

	Vector2 vel1;
	Vector2 vel2;
	
	vel1 = this->GetVelocity();
	vel2 = this->GetVelocity();
	
	if (vel1.x <0.0f)
	{
		vel1.x -= 1.0f;
	}
	else
	{
		vel1.x += 1.0f;
	}

	if(vel1.y < 0.0f)
	{
		vel1.y -= 1.0f;
	}
	else
	{
		vel1.y += 1.0f;
	}

	if (vel2.x <0.0f)
	{
		vel2.x -= 1.0f;
	}
	else
	{
		vel2.x += 1.0f;
	}

	if(vel2.y < 0.0f)
	{
		vel2.y -= 1.0f;
	}
	else
	{
		vel2.y += 1.0f;
	}

	rock1->SetVelocity(vel1.x, vel1.y);
	rock2->SetVelocity(-vel2.x, -vel2.y);

	vel1 = rock1->GetVelocity();
	vel2 = rock2->GetVelocity();

 	rock1->smallRock1Texture = smallRock1ATexture;
	rock1->smallRock2Texture = smallRock2ATexture;
	rock1->smallRock3Texture = smallRock3ATexture;

	rock2->smallRock1Texture = smallRock1BTexture;
	rock2->smallRock2Texture = smallRock2BTexture;
	rock2->smallRock3Texture = smallRock3BTexture;

	gameEngine->GetLayer(2)->AddObjectToLayer(rock1);
	gameEngine->GetLayer(2)->AddObjectToLayer(rock2);

	currentLevel->rocksCount--;
	Destroy();
	SetState(DeadState);
}