#include "CollisionVolumeOBB.h"

#include "../Tools/Calculations.h"
#include "../Tools/Visualizer.h"

CollisionVolumeOBB::CollisionVolumeOBB()
{
}


CollisionVolumeOBB::~CollisionVolumeOBB()
{
}

void CollisionVolumeOBB::ComputeData(Model* inMod, Matrix& inMat)
{
	localMinPoint = inMod->getMinAABB();
	localMaxPoint = inMod->getMaxAABB();
	world = inMat;
}

void CollisionVolumeOBB::ComputeData(Model * pMod, Matrix & mMat, const float & )
{
	ComputeData(pMod, mMat);
}

void CollisionVolumeOBB::DebugView(const Vect & inColor) const
{
	Visualizer::renderOBB(*this, inColor);
}

bool CollisionVolumeOBB::Intersect(const CollisionVolume & other) const
{
	return other.Intersect(*this);
}

bool CollisionVolumeOBB::Intersect(const CollisionVolumeBSphere & other) const
{
	return  Calculations::OBBCollisonTest(this, other);
}

bool CollisionVolumeOBB::Intersect(const CollisionVolumeAABB & other) const
{
	return  Calculations::OBBCollisonTest(this, other);
}

bool CollisionVolumeOBB::Intersect(const CollisionVolumeOBB& other) const
{
	return  Calculations::OBBCollisonTest(this, other);
}