#ifndef _COLLISIONVOLUMEAABB
#define _COLLISIONVOLUMEAABB

#include "AzulCore.h"
#include "../Base Volumes/CollisionVolumeBoundingBox.h"

class CollisionVolumeAABB: public CollisionVolumeBoundingBox
{
public:
	//------------------------------------
	//Big 4
	//------------------------------------
	CollisionVolumeAABB();
	CollisionVolumeAABB(const Vect & inMin, const Vect & inMax);
	~CollisionVolumeAABB();

	void ComputeData(Model* mod, Matrix& mat) override;
	void ComputeData(Model * mod, Matrix & mat, const float& scal)override;
	void DebugView(const Vect & inColor) const override;
	bool Intersect(const CollisionVolume& other) const override;
	bool Intersect(const CollisionVolumeBSphere& other) const override;
	bool Intersect(const CollisionVolumeAABB& other) const override;
	bool Intersect(const CollisionVolumeOBB& other) const override;

	Vect getWorldMax() const;
	Vect getWorldMin() const;

	void setWorldMax(const Vect& inPoint);
	void setWorldMin(const Vect& inPoint);

private:
	Vect worldMinPoint;
	Vect worldMaxPoint;
};

#endif //!_COLLISIONVOLUMEAABB