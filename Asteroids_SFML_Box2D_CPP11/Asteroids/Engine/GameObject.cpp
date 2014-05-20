#include "GameObject.h"
#include "Layer.h"


extern b2World* phyxWorld; 

GameObject::GameObject() : 
	isActive(true),
	objectId(0),
	rotateTextureWithPhysics(true),
	isDestroyed(false),
	pointerPressed(false)
{
	name = "Object";
	meterToPixel = 50.0f;
}


// Empty GameObject. An Empty Gameobject is a minimum GameObject. It has no Texture, and has a minimum collision scale 
GameObject::GameObject(string objectName, Engine* engineRef, bool isDynamic, bool isPhysicsBody, Vector2 &position)
:	isActive(true),
	objectId(0),
	rotateTextureWithPhysics(true),
	isDestroyed(false),
	pointerPressed(false)
{
	meterToPixel = 50.0f;
	// setting the gameobject name 
	name = objectName;

	xDrawScale=1;
	yDrawScale=1;
	xCollisionScale=1;
	yCollisionScale=1;

	// set the current texture to null
	currentTexture = NULL;
	
	// Ref to main Class 
	engineRef = engineRef;
	
	// Setting the game object Position
	position = position;

	xCollisionScale=1;
	yCollisionScale=1; 
	xDrawScale=1;
	yDrawScale=1;

	dynamic = isDynamic;
	isPhyxBody = isPhysicsBody;
	b2BodyDef BodyDef;
	b2PolygonShape Box;			
	BodyDef.position.Set(position.x, position.y);	

	if(dynamic)
	{
		BodyDef.type = b2_dynamicBody;
	}

	b2Body* body;
	body = phyxWorld->CreateBody(&BodyDef);
	body->SetUserData((void*)this);
	Box.SetAsBox(1,1);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &Box;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.8f;
	colliderType = ColliderType::BoxCollider;

	body->CreateFixture(&fixtureDef);
	collisionBox = body;

	if(!isPhyxBody)
	{
		collisionBox->SetActive(false);
	}

	// Setting the original Height and widht
	originalWidth = 1;
	originalHeight = 1;
}

// Seting the Velocity of the gameobject
void GameObject::SetVelocity(float x,float y)
{
	collisionBox->SetLinearVelocity(b2Vec2(x,y));
}

// Full GameObject with texture
GameObject::GameObject(string objectName, Engine* engineRef, bool isDynamic, bool isPhysicsBody, Vector2 &_Position, string _TextureName, bool _IsSprite, int _Rows, int _Columns)
:	isActive(true),
	objectId(0),
	rotateTextureWithPhysics(true),
	isDestroyed(false),
	pointerPressed(false)
{	
	meterToPixel = 50.0f;

	objectId = 0;
	xDrawScale=1;
	yDrawScale=1;
	xCollisionScale=1;
	yCollisionScale=1;

	// Ref to main Class 
	this->engineRef = engineRef;

	// Setting the gameobject name 
	name=objectName;

	AddTexture(_TextureName, _IsSprite, _Rows, _Columns);
	currentTexture = textureHolder.front()->texture;
	currentTexture->SetSize();
	currentTexture->sprite->setTexture(*currentTexture->image);
	//currentTexture->sprite->setPosition(currentTexture->sprite->getPosition().x+(currentTexture->image->getSize().y*0.5f), currentTexture->sprite->getPosition().y-(currentTexture->image->getSize().y*0.5f));
	currentTexture->ResumeSprite();
	currentTexture->owner = this;

	
	// Setting the game object Position
	position.x = _Position.x;
	position.y = _Position.y;

	dynamic = isDynamic;
	isPhyxBody = isPhysicsBody;
	b2BodyDef BodyDef;
	b2PolygonShape Box;			
	BodyDef.position.Set(position.x, position.y);	

	if(dynamic)
	{
		BodyDef.type = b2_dynamicBody;
	}

	b2Body* body;
	body = phyxWorld->CreateBody(&BodyDef);
	body->SetUserData((void*)this);

	//Box.SetAsBox(((currentTexture->image->getSize().x*0.5f)/meterToPixel),((currentTexture->image->getSize().y*0.5f)/meterToPixel), b2Vec2((currentTexture->image->getSize().x*0.5f)/meterToPixel,(currentTexture->image->getSize().y*0.5f)/meterToPixel),  body->GetAngle());
	//Box.SetAsBox((currentTexture->image->getSize().x/100.0f),(currentTexture->image->getSize().y/100.0f)/*, b2Vec2((currentTexture->image->getSize().x*0.5f),(currentTexture->image->getSize().y*0.5f)),  body->GetAngle()*/);
	//Box.SetAsBox(((currentTexture->image->getSize().x*0.5f)),((currentTexture->image->getSize().y*0.5f)), b2Vec2((currentTexture->image->getSize().x*0.5f),(currentTexture->image->getSize().y*0.5f)),  body->GetAngle());
	//Box.SetAsBox(((position.x/meterToPixel)-(currentTexture->image->getSize().x*0.5f)), ((position.y/meterToPixel)-(currentTexture->image->getSize().y*0.5f)), b2Vec2(((position.x/meterToPixel)-(currentTexture->image->getSize().x*0.5f)), ((position.y/meterToPixel)-(currentTexture->image->getSize().y*0.5f))), body->GetAngle());
	//Box.SetAsBox(((currentTexture->image->getSize().x*0.02f)),((currentTexture->image->getSize().y*0.02f)), b2Vec2((currentTexture->image->getSize().x*0.02f),(currentTexture->image->getSize().y*0.02f)),  body->GetAngle());
	//Box.SetAsBox((5.0f)/50,(5.0f)/50);
	Box.SetAsBox((position.x/meterToPixel),(position.y/meterToPixel));
	//Box.SetAsBox(position.x,position.y);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &Box;
	//fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.5f;
	colliderType = ColliderType::BoxCollider;

	body->CreateFixture(&fixtureDef);
	collisionBox = body;

	if(!isPhyxBody)
	{
		collisionBox->SetActive(false);
	}


	// Setting the original Height and width
	originalWidth = currentTexture->image->getSize().x*1.0f;
	originalHeight = currentTexture->image->getSize().y*1.0f;

}

// Gives your Game Object a Tag. Useful for grouping your Objects with a name. For Example you can tag your Environment Objects as "Furniture" or "Explosive", etc
// Which can then be used in various parts of your game. For Example, on collision with other gameobjects, you can test the tag, and if its an "Explosove", you can
// Call a function for simulation explosion etc.
void GameObject::SetTag(string ChangeTo)
{
	tag=ChangeTo;
}

// Gives your game object a unique identifier. Please Note, that if more than one game objects has a same name, then the Engine will automatically append an integer
// at the end of the name to distinguish them. Please always try to give unique names to your game objects to make it easy for you to access them.
void GameObject::SetName(string ChangeTo)
{
	name=ChangeTo;
}

// Sets the Object's gravity scaly. This allows you to set different amount of gravity to different objects.
void GameObject::SetGravity(float gravity)
{
	collisionBox->SetGravityScale(gravity);
}

// Returns the Name of the game object
string GameObject::GetName()
{
	return name;
}

// Returns the Tag of the game object
string GameObject::GetTag()
{
	return tag;
}

// Compares the game object's Tag against the provided string.
// Returns True if they match and False if they do not match
bool GameObject::CompareTag(string TestTo)
{
	if(TestTo.compare(tag)==0)
	{
		return true;
	}
	
	return false;
}

// Compares the game object's Name against the provided string.
// Returns True if they match and False if they do not match
bool GameObject::CompareName(string TestTo)
{
	if(TestTo.compare(name)==0)
	{
		return true;
	}
	return false;
}

// Adds a Texture or Spritesheet to the list of the already existing Textures, if any
void GameObject::AddTexture(string textureName, bool isSprite, int rows, int columns)
{
	textureHolder.push_back(engineRef->textureManager->AddTexture(engineRef, textureName, isSprite, rows, columns));	
}

// Sets the current Texture to the one specified if it exists in the game object's texture list
void GameObject::SetTexture(string texName)
{
	for(textureIterator=textureHolder.begin(); textureIterator!=textureHolder.end(); textureIterator++)
	{	
		TextureEntry * tex = *textureIterator;
		if(tex->textureName.compare(texName)==0)
		{	
			// If the texture is null set this texture as the first one 
			if(currentTexture == NULL)
			{
				originalWidth  = tex->texture->image->getSize().x*1.0f;
				originalHeight = tex->texture->image->getSize().y*1.0f;
			}

			currentTexture = tex->texture;
			currentTexture->sprite->setTexture(*currentTexture->image);
			// Set the texture frame to 0 
			SetTextureFrame();
			return;
		}
	}
	
}

void GameObject::SetPhysicsBody(bool newPhyx)
{ 
	collisionBox->SetActive(newPhyx);
}

void GameObject::SetDynamicBody(bool newDynamic)
{ 		 
	if(newDynamic)
	{
		collisionBox->SetType(b2BodyType::b2_dynamicBody);
	}
	else
	{
		collisionBox->SetType(b2BodyType::b2_staticBody);
	}
}

Layer * GameObject::GetLayer(int layer)
{
	return GameObject::engineRef->GetLayer(layer);
}

Layer * GameObject::GetMyLayer()
{
	return GetLayer(layer);
}

static bool deleteAll(TextureEntry * theElement )
{
	//We're no longer cleaning up textures because they are handled sanely by
	//the TextureManager. We should probably add reference counting to the 
	//TextureManager and release when we are no longer using a particular texture,
	//but for now it's no big deal to keep them in memory.
	//theElement->m_Bitmap.ReleaseAndGetAddressOf();
	//delete theElement; 
	//GameObject::engineRef->m_textureManager->DeleteTexture(theElement->textureName);
	return true; 
}

void GameObject::OnDestroy()
{
	 textureHolder.remove_if(deleteAll);
	 collisionBox->GetWorld()->DestroyBody(collisionBox);
	 delete(this);
}

void GameObject::Destroy()
{
	isDestroyed = true;
	pointerPressed = false;
	GetMyLayer()->RemoveObject(name);
	//delete(this);
}

void GameObject::Render(sf::RenderWindow* renderer/*, sf::Time globalTime*/)
{  
	if(isDestroyed)
	{
		return;
	}
	if (!isActive) return; //Easy way to prevent this gameobject from being rendered

	widthScreen = renderer->getSize().x;
	heightScreen = renderer->getSize().y;
	offsetX = (widthScreen*0.5f)/meterToPixel; //x offset in meters (400/50 = 8). This will put the 0 x-coordinate in the middle of the screen horizontally.
	offsetY = (heightScreen*0.5f)/meterToPixel; //y offset in meters (300/50 = 6). This will put the 0 y-coordinate in the middle of the screen vertically.
	//offsetX = (widthScreen*0.02f); //x offset in meters (400/50 = 8). This will put the 0 x-coordinate in the middle of the screen horizontally.
	//offsetY = (heightScreen*0.02f); //y offset in meters (300/50 = 6). This will put the 0 y-coordinate in the middle of the screen vertically.
	//offsetX = 0.0f;
	//offsetY = 0.0f;
	drawPositionX = (position.x + offsetX) * meterToPixel; //( (0m) +  8.0m )* 50 = 400 pixels
	drawPositionY = (-position.y + offsetY) * meterToPixel; //( -(4m) + 6.0m ) * 50 = 100 pixels

	drawPositionX -= currentTexture->image->getSize().x*0.5f;
	drawPositionY -= currentTexture->image->getSize().y*0.5f;

	this;

	currentTexture->sprite->setRotation(GetRotationAngle());
	currentTexture->sprite->setPosition(drawPositionX, drawPositionY);
	//currentTexture->sprite->setPosition(position.x, position.y);
	currentTexture->sprite->setScale(xDrawScale, yDrawScale);
	//currentTexture->renderer = renderer;
	//currentTexture->globalTime = globalTime;
	
	
	// If the Texture is null then no need to draw a bitmap
	if(currentTexture != nullptr)
	{
		// Set the current texture
		currentTexture->PlaySprite(/*currentAnim*/);
		// Draw Bitmap
		renderer->draw(*currentTexture->sprite, sf::RenderStates::Default);
		//collisionBox
	}

	position =  Vector2(collisionBox->GetPosition().x, collisionBox->GetPosition().y);
	angle = collisionBox->GetAngle();	
		
}


Vector2 GameObject::GetMainCameraPosition()
{	
	//return Vector2(-GameObject::engineRef->GetMainCameraPosition()._31/50,GameObject::engineRef->GetMainCameraPosition()._32/50);
	return Vector2(0.0f,0.0f);
}

string GameObject::GetTextureName()
{
	if (currentTexture == nullptr)
	{
		return "";
	}

	return currentTexture->textureName;
}

void GameObject::RotateToLookAt(float x,float y)
{
	RotateToLookAt(Vector2(x,y));
}

void GameObject::RotateToLookAt(Vector2 lookAt)
{
	float bodyAngle = collisionBox->GetAngle();
    b2Vec2 toTarget = b2Vec2(lookAt.x,lookAt.y) - collisionBox->GetPosition();
    float desiredAngle = atan2f( -toTarget.x, toTarget.y );
	collisionBox->SetTransform( collisionBox->GetPosition(), desiredAngle );
	collisionBox->SetAngularVelocity(0);
}

void GameObject::TranslateVelocity (float x,float y, Coordinate rotationCoords)
{
	TranslateVelocity(Vector2(x,y),rotationCoords);
}

/// Translate Object relative to Local space or global
void GameObject::TranslateVelocity (Vector2 direction, Coordinate rotCoords)
{
	if(rotCoords == Local)
	{
		b2Vec2 forward =collisionBox->GetWorldVector(b2Vec2(direction.x,direction.y));
		collisionBox->SetLinearVelocity(forward);			
	}
	else if(rotCoords == Global)
	{
		collisionBox->SetLinearVelocity(b2Vec2(direction.x, direction.y));
	}
}

Vector2 GameObject::GetVelocity()
{
	return Vector2(collisionBox->GetLinearVelocity().x,collisionBox->GetLinearVelocity().y);
}

float GameObject::GetVelocitySize()
{
	return collisionBox->GetLinearVelocity().Length();
}

void GameObject::AddForce (float x,float y, Coordinate rotCoords)
{
	AddForce(Vector2(x,y),rotCoords);
}

void GameObject::AddForce(Vector2 direction, Coordinate rotCoords)
{
	if(rotCoords == Local)
	{
		b2Vec2 forward =collisionBox->GetWorldVector(b2Vec2(direction.x,direction.y));
		if(forward.y>0.0f || forward.y <0.0f)
		{
			if(forward.x>0.25f || forward.x <-0.25f)
			{
				forward.x = -forward.x;
			}
		}
		collisionBox->ApplyForceToCenter(forward, true);
	}
	else if(rotCoords == Global)
	{
		collisionBox->ApplyForceToCenter(b2Vec2(direction.x, direction.y), true);
	}
}

void GameObject::SetDrawScale (Vector2 scale)
{
	SetDrawScale(scale.x,scale.y);
}

void GameObject::SetDrawScale(float x,float y)
{
	xDrawScale=x;
	yDrawScale=y;
}

// Set the Collision Scale(X,Y) Of the GameObject 
void GameObject::SetCollisionScale(float x,float y)
{
	// Only the Box Colliders Can Scale 
	if(colliderType == ColliderType::BoxCollider)
	{
		float _GetFriction =0;// collisionBox->GetFixtureList()->GetFriction();
		float _GetDensity=1;// collisionBox->GetFixtureList()->GetDensity();

		collisionBox->DestroyFixture(collisionBox->GetFixtureList());
		b2PolygonShape Box;
		Box.SetAsBox((originalWidth*0.5f*x)/50,( originalHeight*0.5f*y)/50);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &Box;
		fixtureDef.density = _GetDensity;
		fixtureDef.friction = _GetFriction;
		collisionBox->CreateFixture(&fixtureDef);
		xCollisionScale=x;
		yCollisionScale=y;
	}
	else
	{
		assert(false && "You can only scale Box Colliders...");  
	}


}

// Set the Collision Scale(Vector2) Of the GameObject 
void GameObject::SetCollisionScale (Vector2 scale)
{
	SetCollisionScale(scale.x,scale.y);
}

// Set the GameObject Draw And Collision Scale (Vector2)
void GameObject::SetScale(Vector2 &scale)
{
	SetCollisionScale(scale.x,scale.y);
	SetDrawScale(scale.x,scale.y);
}

// Set the GameObject Draw And Collision Scale (X,Y)
void GameObject::SetScale(float x,float y)
{
	SetDrawScale(x,y);

	//We can't set the collider to exactly 0.0 or the physics engine will assert
	SetCollisionScale((x==0.0f)?0.0001f:x,(y==0.0f)?0.0001f:y);
}

// Return the Collision Scale of the Gameobject 
Vector2 GameObject::GetCollisionScale()
{
	return Vector2(xCollisionScale,yCollisionScale);
}

// Return the Draw Scale of the Gameobject 
Vector2 GameObject::GetDrawScale()
{	
	return Vector2(xDrawScale,yDrawScale);
}

// Rotate GameObject in a given point(Vector2) and angle 
void GameObject::RotateAroundALocalPoint(float angle,Vector2 point)
{	
	RotateAroundALocalPoint(angle,point.x,point.y);
}

// Rotate GameObject in a given point(X,Y) and angle 
void GameObject::RotateAroundALocalPoint(float angle, float x, float y)
{	
	b2Vec2 vertexLocalPos=b2Vec2(x,y);//fulcrum vertex in local (body) coords
	b2Vec2 vertexBeforeWorldPos = collisionBox->GetWorldPoint( vertexLocalPos );
	collisionBox->SetTransform( collisionBox->GetPosition(), collisionBox->GetAngle() + angle );
	b2Vec2 vertexAfterWorldPos =  collisionBox->GetWorldPoint(b2Vec2(x,y));
	collisionBox->SetTransform( collisionBox->GetPosition() + vertexBeforeWorldPos - vertexAfterWorldPos, collisionBox->GetAngle() );
}

Vector2 GameObject::GetGlobalPositionLocalOffset(Vector2 point)
{	
	return GetGlobalPositionLocalOffset(point.x,point.y);
}

Vector2 GameObject::GetGlobalPositionLocalOffset(float x, float y)
{	
	b2Vec2 vertexLocalPos=b2Vec2(x,y);//fulcrum vertex in local (body) coords
	b2Vec2 vertexBeforeWorldPos = collisionBox->GetWorldPoint( vertexLocalPos );
	return Vector2(vertexBeforeWorldPos.x,vertexBeforeWorldPos.y);
}

// Set the position(Vector2) of the GameObject 
void GameObject::SetPosition(Vector2 &point)
{
	SetPosition(point.x,point.y);
}

// Set the position(X,V) of the GameObject 
void GameObject::SetPosition(float x,float y)
{
	collisionBox->SetTransform(b2Vec2(x,y), collisionBox->GetAngle());
}

// Rotate Around GameObject Center point 
void GameObject::Rotate(float angle)
{
	collisionBox->SetTransform( collisionBox->GetPosition(), collisionBox->GetAngle()+angle);
}

// Set the rotation of the GameObject 
void GameObject::SetRotation(float angle)
{
	collisionBox->SetTransform( collisionBox->GetPosition(), angle / 57.2957795f); // Convert Angle From Radians to Degrees 
}


// Translate the game object to a given point(X,Y) in local or global coordinate 
void GameObject::Translate(float x,float y, Coordinate rotCoords)
{
	Translate(Vector2(x,y),rotCoords);
}

// Translate the game object to a given point(Vector2) in local or global coordinate 
void GameObject::Translate(Vector2 direction, Coordinate rotCoords)
{
	if(rotCoords == Local)
	{
		b2Vec2 forward =collisionBox->GetWorldVector(b2Vec2(direction.x,direction.y));
		collisionBox->SetTransform( collisionBox->GetPosition()+forward, collisionBox->GetAngle());	
	}
	else if(rotCoords == Global)
	{
		collisionBox->SetTransform( collisionBox->GetPosition()+b2Vec2(direction.x,direction.y), collisionBox->GetAngle());
	}
}

// Set the GameObject to rotate with the physics or not  
void GameObject::FixRotation(bool fixRot)
{
	collisionBox->SetFixedRotation(fixRot);
}

// Run the animation for the texture
// Animation will start from the 0th frame 
void GameObject::PlaySpriteTexture()
{	
	SetTextureFrame(0);
	currentTexture->ResumeSprite();
}

// Pause the animation for the texture
void GameObject::PauseSpriteTexture()
{	
	currentTexture->PauseSprite();
}
	
// Resume the animation for the texture
void GameObject::ResumeSpriteTexture()
{	
	currentTexture->ResumeSprite();
}

// Set the default frame 
void GameObject::SetTextureFrame()
{
	SetTextureFrame(0);
}

// Setting the animation speed of sprite texture 
void GameObject::SetAnimationSpeed(float speed)
{
	currentTexture->SetFrameSpeed(speed);
}

// Set the given frame 
void GameObject::SetTextureFrame(int frameNumber)
{
	currentTexture->SetTextureFrame(frameNumber);
}

// Return the current Texture Frame number
int GameObject::GetCurrentTextureFrame()
{
	return currentTexture->currentFrame;
	//return 0;
}

// Is the Texture Playing 
bool GameObject::IsPlayingTexture()
{
	//return m_CurrentTexture->IsPlaying();
	return false;
}

bool GameObject::IsDynamic()
{
	return dynamic;
}

// RayCasting from game object position
// 1 radian = 57.2957795 degrees
bool GameObject::RayCast(float angle, float lenght, string tag)
{
	b2RayCastInput input;
	input.p1 = b2Vec2(this->position.x, this->position.y);
	input.p2 = b2Vec2(sin(angle*0.01745f)+this->position.x, cos(angle*0.01745f)+this->position.y);
	input.maxFraction = lenght;

	GameObject* object1; 

	for(b2Body* b=phyxWorld->GetBodyList(); b; b=b->GetNext())
	{
		object1 = (GameObject*)b->GetUserData();
		if(object1->CompareTag(tag))
		{
			if(b!=collisionBox)
			{
				for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
				{
					b2Transform transform;
					transform.SetIdentity();
					b2RayCastOutput output;
					if (f->RayCast(&output, input, 0 ))
					{
						return true;
					}  
				}
			}
		}
	}
	return false;

}

// RayCasting from given position
bool  GameObject::RayCast(Vector2 startPoint,float angle, float lenght, string tag)
{
	b2RayCastInput input;
	input.p1 = b2Vec2(startPoint.x, startPoint.y);
	input.p2 = b2Vec2(sin(angle*0.01745f)+startPoint.x, cos(angle*0.01745f)+startPoint.y);
	input.maxFraction = lenght;

	GameObject* object1; 

	for(b2Body* b=phyxWorld->GetBodyList(); b; b=b->GetNext())
	{
		object1 = (GameObject*)b->GetUserData();
		if(object1->CompareTag(tag))
		{
			if(b!=collisionBox)
			{
				for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
				{
					b2Transform transform;
					transform.SetIdentity();
					b2RayCastOutput output;
					if (f->RayCast(&output, input, 0 ))
					{
						return true;
					}  
				}
			}
		}
	}
	return false;
}

// Retrun the Width(X) and Height (Y) of the gameobject
Vector2 GameObject::GetWidthAndHeight()
{
	return Vector2((originalWidth * 0.5f)/50,(originalHeight * 0.5f)/50);
}

// Trigger the collider 
void GameObject::IsTrigger(bool trigger)
{
	collisionBox->GetFixtureList()->SetSensor(trigger);
}

// Return the trigger information
bool GameObject::IsTriggered()
{
	return collisionBox->GetFixtureList()->IsSensor();
}

// Return the current gameobject angle
float GameObject::GetRotationAngle()
{
	// 1 radian = 57.2957795 degree
	return (angle * 57.2957795f);
}

// Set the Friction Of the Game Object
void GameObject::SetFriction(float friction)
{
	collisionBox->GetFixtureList()->SetFriction(friction);
	collisionBox->GetFixtureList()->Refilter();
}

// Set the Density Of the Game Object
void GameObject::SetDensity(float density)
{
	collisionBox->GetFixtureList()->SetDensity(density);
	collisionBox->ResetMassData();
}

// Set the damping of the object
// Damping is used to reduce the world velocity of gameobject
void GameObject::SetDamping(float damp)
{
	collisionBox->SetLinearDamping(damp);
}

// Set the damping of the object
// Damping is used to reduce the world velocity of gameobject
void GameObject::SetAngularDamping(float damp)
{
	collisionBox->SetAngularDamping(damp);
}

// Set the Sphere collision's to GameObject
void GameObject::SetCollisionToSphere(float radius)
{
	 float density=collisionBox->GetFixtureList()->GetDensity();
	 float friction=collisionBox->GetFixtureList()->GetFriction();
	 collisionBox->DestroyFixture(collisionBox->GetFixtureList());
	 b2CircleShape circle ;
	 circle.m_radius = radius;

	 b2FixtureDef fixtureDef;
	 fixtureDef.shape = &circle;
	 fixtureDef.density = density;
	 fixtureDef.friction = friction;
	 colliderType = ColliderType::SphereCollider;

	 collisionBox->CreateFixture(&fixtureDef);
	 xCollisionScale=radius;
	 yCollisionScale=radius;
}

// Set the Custom Collision's to GameObject
void GameObject::SetCollisionToCustom(const b2Vec2* vertices,int numOfVertices)
{
	 float density=collisionBox->GetFixtureList()->GetDensity();
	 float friction=collisionBox->GetFixtureList()->GetFriction();
	 collisionBox->DestroyFixture(collisionBox->GetFixtureList());
	 b2PolygonShape polygonShape;
	 polygonShape.Set(vertices, numOfVertices);

	 b2FixtureDef fixtureDef;
	 fixtureDef.shape = &polygonShape;
	 fixtureDef.density = density;
	 fixtureDef.friction = friction;
	 // Set the Collider type to Custom
	 colliderType = ColliderType::CustomCollider;

	 collisionBox->CreateFixture(&fixtureDef);
	 xCollisionScale=1;
	 yCollisionScale=1;
}

void GameObject::AddAnimation(string animName, Animation newAnim)
{
	AnimationData newData;
	newData.animName = animName;
	newData.anim = newAnim;
	animations.push_back(newData);
}