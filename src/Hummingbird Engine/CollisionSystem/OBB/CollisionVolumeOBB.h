#ifndef _CollisionVolumeOBB
#define _CollisionVolumeOBB

#include "AzulCore.h"
#include "../Base Volumes/CollisionVolumeBoundingBox.h"

class CollisionVolumeOBB: public CollisionVolumeBoundingBox
{
public:
	//------------------------------------
	//Big 4
	//------------------------------------
	CollisionVolumeOBB();
	~CollisionVolumeOBB();

	/// <summary>
	/// Computes the Min and Max points(World and Local) for the OBB.
	/// </summary>
	/// <param name="mod">The gameobjects model.</param>
	/// <param name="mat">The current world matrix position.</param>
	void ComputeData(Model* mod, Matrix& mat) override;

	/// <summary>
	/// Specialized Compute: "Faster" since you dont have to deconstuct the World Matrix.
	/// Computes the Min and Max points(World and Local) for the OBB.
	/// </summary>
	/// <param name="mod">The gameobjects model.</param>
	/// <param name="mat">The current world matrix position.</param>
	/// <param name="scal">The scale(equal scaling on all axis) of the model.</param>
	void ComputeData(Model * mod, Matrix & mat, const float& scal)override;
	/// <summary>
	/// Call for the Visualizer to render the OBB.
	/// </summary>
	/// <param name="inColor">Color of the OBB.</param>
	void DebugView(const Vect & inColor) const override;
	/// <summary>
	/// Specialized: Used for Double Dispatch.
	/// Checks if there is an intersection with this and a given Volume. 
	/// </summary>
	/// <param name="other">The other volume.</param>
	/// <returns> Returns True if this collided with the other Volume.</returns>
	bool Intersect(const CollisionVolume& other) const override;
	/// <summary>
	/// Checks if there is an intersection with this and a BSphere. 
	/// </summary>
	/// <param name="other">Given BSphere.</param>
	/// <returns> Returns True if this collided with the given BSphere.</returns>
	bool Intersect(const CollisionVolumeBSphere& other) const override;
	/// <summary>
	/// Checks if there is an intersection with this and a AABB. 
	/// </summary>
	/// <param name="other">Given AABB.</param>
	/// <returns>Returns True if this collided with the given AABB.</returns>
	bool Intersect(const CollisionVolumeAABB& other) const override;
	/// <summary>
	/// Checks if there is an intersection with this and a OBB. 
	/// </summary>
	/// <param name="other">Given OBB.</param>
	/// <returns>Returns True if this collided with the given OBB.</returns>
	bool Intersect(const CollisionVolumeOBB& other) const override;
};

#endif //!_CollisionVolumeOBB