#pragma once


class CollisionListener : public b2ContactListener
{
public:
	CollisionListener(void);
	~CollisionListener(void);
	void BeginContact(b2Contact* contact);
};

