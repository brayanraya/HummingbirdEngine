#include "CollisionVolume.h"


#include "../Bounding Sphere/CollisionVolumeBSphere.h"
#include "../AABB/CollisionVolumeAABB.h"
#include "../../Scene Manager/Attributes/Collidable/collideable.h"

CollisionVolume::CollisionVolume()
{
	
}

CollisionVolume::~CollisionVolume()
{
}

void CollisionVolume::ComputeData(Model*, Matrix&)
{
}

void CollisionVolume::ComputeData(Model*, Matrix&, const float&)
{
}

void CollisionVolume::DebugView(const Vect &) const
{
}

bool CollisionVolume::Intersect(const CollisionVolume& ) const
{
	return false;
}

bool CollisionVolume::Intersect(const CollisionVolumeBSphere& ) const
{
	return false;
}

bool CollisionVolume::Intersect(const CollisionVolumeAABB & ) const
{
	return false;
}

bool CollisionVolume::Intersect(const CollisionVolumeOBB & ) const
{
	return false;
}
