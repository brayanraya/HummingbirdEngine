#ifndef _CollisionVolumeBoundingBox
#define _CollisionVolumeBoundingBox

#include "AzulCore.h"
#include "CollisionVolume.h"

class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class collideable;
/// <summary>	A general collision volume. </summary>
class CollisionVolumeBoundingBox: public CollisionVolume
{
public:
	//------------------------------------
	//Big 4
	//------------------------------------

	CollisionVolumeBoundingBox();
	~CollisionVolumeBoundingBox();

	//------------------------------------
	//Used By Both AABB and OBB
	//------------------------------------

	/// <summary>
	/// Gets the local maximum in WorldSpace.
	/// </summary>
	/// <returns> Max Local Point.</returns>
	Vect getLocalMax() const;
	/// <summary>
	/// Gets the local minimum.
	/// </summary>
	/// <returns>Vect.</returns>
	Vect getLocalMin() const;
	/// <summary>
	/// Gets the world.
	/// </summary>
	/// <returns>Matrix.</returns>
	Matrix getWorld() const;

protected:
	Matrix world;
	Vect localMinPoint;
	Vect localMaxPoint;
};

#endif //!_CollisionVolume