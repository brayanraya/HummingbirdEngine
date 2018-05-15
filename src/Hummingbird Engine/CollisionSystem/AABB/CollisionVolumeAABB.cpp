#include "CollisionVolumeAABB.h"

#include "../Tools/Visualizer.h"
#include "../Tools/Calculations.h"

CollisionVolumeAABB::CollisionVolumeAABB()
{
	worldMinPoint = Vect();
	worldMaxPoint = Vect();
}

CollisionVolumeAABB::CollisionVolumeAABB(const Vect& inMin, const Vect& inMax)
{
	worldMinPoint = inMin;
	worldMaxPoint = inMax;
}
CollisionVolumeAABB::~CollisionVolumeAABB()
{
}

void CollisionVolumeAABB::ComputeData(Model* inMod, Matrix& inMat )
{
	world = inMat;
	localMinPoint = inMod->getMinAABB();
	localMaxPoint = inMod->getMaxAABB();

	Vect TempMin = inMod->getVectList()[0] * inMat;
	Vect TempMax = TempMin;

	Vect modify;

	for (int i = 0; i < inMod->getVectNum(); i++)
	{
		modify = inMod->getVectList()[i] * inMat;

		if (modify.X() < TempMin.X())
		{
			TempMin.X() = modify.X();
		}
		if (modify.Y() < TempMin.Y())
		{
			TempMin.Y() = modify.Y();
		}
		if (modify.Z() < TempMin.Z())
		{
			TempMin.Z() = modify.Z();
		}
		if (modify.X() > TempMax.X())
		{
			TempMax.X() = modify.X();
		}
		if (modify.Y() > TempMax.Y())
		{
			TempMax.Y() = modify.Y();
		}
		if (modify.Z() > TempMax.Z())
		{
			TempMax.Z() = modify.Z();
		}
	}
	worldMinPoint = TempMin;
	worldMaxPoint = TempMax;
}

void CollisionVolumeAABB::ComputeData(Model * inMod, Matrix & inMat, const float &)
{
	ComputeData(inMod, inMat);
}

void CollisionVolumeAABB::DebugView(const Vect & inColor) const
{
	Visualizer::renderAABB(*this, inColor);
}

bool CollisionVolumeAABB::Intersect(const CollisionVolume& other) const
{
	return other.Intersect(*this);
}

bool CollisionVolumeAABB::Intersect(const CollisionVolumeBSphere & other) const
{
	return Calculations::AABBCollisonTest(this, other);
}

bool CollisionVolumeAABB::Intersect(const CollisionVolumeAABB & other) const
{
	return Calculations::AABBCollisonTest(this, other);
}

bool CollisionVolumeAABB::Intersect(const CollisionVolumeOBB & other) const
{
	return Calculations::AABBCollisonTest(this, other);
}

Vect CollisionVolumeAABB::getWorldMax()const
{
	return worldMaxPoint;
}

Vect CollisionVolumeAABB::getWorldMin()const
{
	return worldMinPoint;
}

void CollisionVolumeAABB::setWorldMax(const Vect& inPoint)
{
	worldMaxPoint = inPoint;
}

void CollisionVolumeAABB::setWorldMin(const Vect& inPoint)
{
	worldMinPoint = inPoint;
}
