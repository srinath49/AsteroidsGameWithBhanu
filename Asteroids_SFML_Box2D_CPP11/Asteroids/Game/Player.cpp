#include "Player.h"
#include "Bullet.h"

void Player::BeginContact(GameObject* object)
{
	if(object->CompareTag("Rock"))
	 {
  		SetState(DyingState);
		this;
	}	
}

void Player::EndContact(GameObject*)
{
}

void Player::Start()
{
	IsTrigger(true);
	SetGravity(0.0f);
	SetVelocity(0.0f,0.0f);
	SetFriction(0.1f);
	SetDamping(0.4f);
	SetAngularDamping(1.0f);
	lives = 3;
}

void Player::Update(unsigned long frameNumber)
{
	switch(currentState)
	{
		case DyingState:
     			lives--;
			if(lives <= 0)
			{
				Destroy();
				currentLevel->PlayerNull();
			}
			else
			{
				SetPosition(0,0);
			}
			SetState(NormalState);
			break;
	}
}

string Player::GetType()
{
	return "Player";
}

void Player::OnPointerPressed(Vector2 _Point)
{

}

void Player::OnPointerMoved(Vector2 _Point)
{
}

void Player::OnPointerReleased(Vector2 _Point)
{
}

void Player::SetState(PlayerState _NewState)
{
	previousState = currentState;
	currentState = _NewState;
}


/*
string Player::IntString(int intToConvert)
{
	//string ret; 
	//_itow_s(intToConvert, ret, 10);
	return "";
}
*/

void Player::OnKeyPressed(sf::Keyboard::Key pressedKey)
{
	if(currentState == DyingState)
	{
		return;
	}

	switch(pressedKey)
	{
		case sf::Keyboard::Up:
			MovePlayer(MoveDirection::Up);
			break;
		case sf::Keyboard::Down:
			MovePlayer(MoveDirection::Down);
			break;
		case sf::Keyboard::Right:
			RotatePlayer(RotationAngle::Right);
			break;
		case sf::Keyboard::Left:
			RotatePlayer(RotationAngle::Left);
			break;
		case sf::Keyboard::Space:
			Fire();
			break;
	}
}

void Player::OnKeyReleased(sf::Keyboard::Key releasedKey)
{
	if(currentState == DyingState)
	{
		return;
	}

	switch(releasedKey)
	{
		case sf::Keyboard::Right:
			break;
		case sf::Keyboard::Left:
			break;
		case sf::Keyboard::Up:
			break;
		case sf::Keyboard::Down:
			break;
	}
}

void Player::MovePlayer(MoveDirection direction)
{
	if(currentState == DyingState)
	{
		return;
	}

	if(GetVelocitySize() >= 8.0)
	{
		return;
	}
	switch(direction)
	{
		case Up: AddForce(0.0f, 7.0f, Coordinate::Local);
			break;
		case Down: AddForce(0.0f, -7.0f, Coordinate::Local);
			break;
	}
}

void Player::RotatePlayer(RotationAngle angle)
{
	if(currentState == DyingState)
	{
		return;
	}

	if(collisionBox->GetAngularVelocity() >= 5.0)
	{
		return;
	}
	switch(angle)
	{
		case Right: collisionBox->SetAngularVelocity(collisionBox->GetAngularVelocity()+0.675f);
			//collisionBox->SetTransform(collisionBox->GetPosition(), this->GetRotationAngle()+0.075f);
			break;
		case Left: collisionBox->SetAngularVelocity(collisionBox->GetAngularVelocity()-0.675f);
			//collisionBox->SetTransform(collisionBox->GetPosition(), this->GetRotationAngle()-0.075f);
			break;
	}
}


void Player::Fire()
{
	if(currentState == DyingState)
	{
		return;
	}

	Bullet* newBullet = new Bullet("Bullet", gameEngine, true, true, position, "bullet.png", false, 1, 1);
 	newBullet->SetRotation(this->GetRotationAngle());
	gameEngine->GetLayer(2)->AddObjectToLayer(newBullet);
}
