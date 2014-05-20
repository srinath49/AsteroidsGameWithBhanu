#include "MyQueryCallback.h"


bool MyQueryCallback::ReportFixture(b2Fixture* fixture)
{
    foundBodies.push_back( fixture->GetBody() ); 
    return true;//keep going to find all fixtures in the query area
}
