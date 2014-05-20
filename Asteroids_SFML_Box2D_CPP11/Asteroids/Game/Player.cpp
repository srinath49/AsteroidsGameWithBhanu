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
	SetDamping(1.0f);
	SetAngularDamping(1.5f);
	lives = 3;
	SetState(NormalState);
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
				SetState(NormalState);
			}
			SetState(NormalState);
			break;
		case NormalState:
			CheckCoordinates();
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
			SlowRotate();
			break;
		case sf::Keyboard::Left:
			SlowRotate();
			break;
		case sf::Keyboard::Up:
			SlowMove();
			break;
		case sf::Keyboard::Down:
			SlowMove();
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

	if(collisionBox->GetAngularVelocity() >= 3.0)
	{
		return;
	}
	switch(angle)
	{
		case Right: //collisionBox->SetAngularVelocity(collisionBox->GetAngularVelocity()+0.05f);
			//collisionBox->SetTransform(collisionBox->GetPosition(), this->GetRotationAngle()+0.075f);
			Rotate(0.01f);
			break;
		case Left: //collisionBox->SetAngularVelocity(collisionBox->GetAngularVelocity()-0.05f);
			//collisionBox->SetTransform(collisionBox->GetPosition(), this->GetRotationAngle()-0.075f);
			Rotate(-0.01f);
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


void Player::SlowMove()
{
	SetVelocity(GetVelocity().x*0.5f, GetVelocity().y*0.5f);
}

void Player::SlowRotate()
{
	collisionBox->SetAngularVelocity(collisionBox->GetAngularVelocity());
}

void Player::CheckCoordinates()
{
	if(position.x < -10.0f)
	{
		SetPosition(9.5f, position.y);
	}
	else if(position.x > 10.0f)
	{
		SetPosition(-9.5f, position.y);
	}

	if(position.y < -8.0f)
	{
		SetPosition(position.x, 7.5f);
	}
	else if(position.y > 8.0f)
	{
		SetPosition(position.x, -7.5f);
	}
}