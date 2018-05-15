#include "CollisionVolumeBoundingBox.h"

#include "../Bounding Sphere/CollisionVolumeBSphere.h"
#include "../AABB/CollisionVolumeAABB.h"
#include "../OBB/CollisionVolumeOBB.h"
#include "../../Scene Manager/Attributes/Collidable/collideable.h"

CollisionVolumeBoundingBox::CollisionVolumeBoundingBox()
{
	localMaxPoint = Vect();
	localMaxPoint = Vect();
	world = Matrix(IDENTITY);
}

CollisionVolumeBoundingBox::~CollisionVolumeBoundingBox()
{
}

Vect CollisionVolumeBoundingBox::getLocalMax()const
{
	return localMaxPoint;
}

Vect CollisionVolumeBoundingBox::getLocalMin()const
{
	return localMinPoint;
}

Matrix CollisionVolumeBoundingBox::getWorld() const
{
	return world;
}