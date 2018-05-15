#ifndef _collideableGroupBase
#define _collideableGroupBase

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	An empty base that all collideable groups derive from to be added to the collidable managers list. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "AzulCore.h"

class CollisionVolumeAABB;

class collideableGroupBase
{
public:
	//------------------------------------
	// Big 4. 
	//------------------------------------
	collideableGroupBase();
	~collideableGroupBase();

	
protected:
	CollisionVolumeAABB* groupsAABB;
	Vect* groupsMin;
	Vect* groupsMax;
};

#endif // !_collideableGroupBase