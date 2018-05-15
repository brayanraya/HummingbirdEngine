#include "collideableGroupBase.h"

#include "../../../CollisionSystem/AABB/CollisionVolumeAABB.h"

collideableGroupBase::collideableGroupBase()
{
	
	groupsMin = new Vect(-9999.0f, -9999.0f, -9999.0f);
	groupsMax = new Vect(-9999.0f, -9999.0f, -9999.0f);
	groupsAABB = new CollisionVolumeAABB(*groupsMin, *groupsMax);
}


collideableGroupBase::~collideableGroupBase()
{
	delete groupsAABB;
	delete groupsMin;
	delete groupsMax;
}