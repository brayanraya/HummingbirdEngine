#include "CollisionVolumeBSphere.h"

#include "../Tools/Calculations.h"
#include "../Tools/Visualizer.h"

CollisionVolumeBSphere::CollisionVolumeBSphere()
{
}


CollisionVolumeBSphere::~CollisionVolumeBSphere()
{
}

void CollisionVolumeBSphere::ComputeData(Model * mod, Matrix & mat)
{
	Center = mod->getCenter();
	Center *= mat;
	Radius = mod->getRadius();
	Radius *= Calculations::ScaleFromWorld(mat);
}

void CollisionVolumeBSphere::ComputeData(Model * mod, Matrix & mat, const float& scal)
{
	Center = mod->getCenter();
	Center *= mat;
	Radius = mod->getRadius();
	Radius *= scal;
}

const Vect & CollisionVolumeBSphere::GetCenter() const
{
	return Center;
}

float CollisionVolumeBSphere::GetRadius() const
{
	return Radius;
}

bool CollisionVolumeBSphere::Intersect(const CollisionVolume & other) const
{
	return other.Intersect(*this);
}

bool CollisionVolumeBSphere::Intersect(const CollisionVolumeBSphere & other) const
{
	return Calculations::bSphereCollisonTest(this,other);
}

bool CollisionVolumeBSphere::Intersect(const CollisionVolumeAABB & other) const
{
	return Calculations::bSphereCollisonTest(this, other);
}

bool CollisionVolumeBSphere::Intersect(const CollisionVolumeOBB & other) const
{
	return Calculations::bSphereCollisonTest(this, other);
}

void CollisionVolumeBSphere::DebugView(const Vect & inColor) const
{
	Visualizer::renderBSphere(*this, inColor);
}

Matrix CollisionVolumeBSphere::getWorld() const
{
	return world;
}
