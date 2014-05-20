#pragma once

#include "Box2D.h"
#include <vector>

class MyQueryCallback :
	public b2QueryCallback
{
public:
	std::vector<b2Body*> foundBodies;
      
    bool ReportFixture(b2Fixture* fixture);
};

