#ifndef _CollisionVolume
#define _CollisionVolume

#include "AzulCore.h"
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class collideable;

/// <summary>	An abstract collision volume that will be inherited by other. </summary>
class CollisionVolume: public Align16
{
public:
	//------------------------------------
	//Big 4
	//------------------------------------
	CollisionVolume();
	~CollisionVolume();

	virtual void ComputeData(Model* mod, Matrix& mat) = 0;
	virtual void ComputeData(Model * mod, Matrix & mat, const float& scal) = 0;
	virtual void DebugView(const Vect & inColor) const = 0;
	virtual bool Intersect(const CollisionVolume& other) const = 0;
	virtual bool Intersect(const CollisionVolumeBSphere& other) const = 0;
	virtual bool Intersect(const CollisionVolumeAABB& other) const = 0;
	virtual bool Intersect(const CollisionVolumeOBB& other) const = 0;
};

#endif //!_CollisionVolume