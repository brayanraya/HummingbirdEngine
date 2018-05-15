#ifndef _CollisionVolumeBSphere
#define _CollisionVolumeBSphere

#include "AzulCore.h"
#include "../Base Volumes/CollisionVolume.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Volume and movement caluclations for the volume of bsphere. </summary>
///
/// <remarks>	Braya, 3/2/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class CollisionVolumeBSphere: public CollisionVolume
{
public:
	//------------------------------------
	//Big 4
	//------------------------------------
	CollisionVolumeBSphere();
	~CollisionVolumeBSphere();


	/// <summary>
	/// Computes the centerPoint(World) and the radius of the BSphere.
	/// </summary>
	/// <param name="mod">The mod.</param>
	/// <param name="mat">The mat.</param>
	void ComputeData(Model* mod, Matrix& mat) override;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Calculates the data. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="mod"> 	[in,out] If non-null, the modifier. </param>
	/// <param name="mat"> 	[in,out] The matrix. </param>
	/// <param name="scal">	The scal. </param>
	///-------------------------------------------------------------------------------------------------
	void ComputeData(Model * mod, Matrix & mat, const float& scal)override;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Returns the center. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <returns>	The center of the Bsphere. </returns>
	///-------------------------------------------------------------------------------------------------
	const Vect& GetCenter() const;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the radius. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <returns>	The radius. </returns>
	///-------------------------------------------------------------------------------------------------
	float GetRadius() const;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Intersects the given other. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="other">	The other. </param>
	///
	/// <returns>	True if it succeeds, false if it fails. </returns>
	///-------------------------------------------------------------------------------------------------
	bool Intersect(const CollisionVolume& other) const override;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Intersects the given other. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="other">	The other. </param>
	///
	/// <returns>	True if BSphere intersects with another BSphere. </returns>
	///-------------------------------------------------------------------------------------------------
	bool Intersect(const CollisionVolumeBSphere& other) const override;


	/// <summary>
	/// Intersects the specified other.
	/// </summary>
	/// <param name="other">The AABB.</param>
	/// <returns> True if BSphere intersects with an AABB.</returns>
	bool Intersect(const CollisionVolumeAABB& other) const override;

	/// <summary>
	/// Intersects the specified other.
	/// </summary>
	/// <param name="other">The other.</param>
	/// <returns> True if BSphere intersects with an OBB.</returns>
	bool Intersect(const CollisionVolumeOBB& other) const override;


	/// <summary>
	/// Call for the Visualizer to render the BSphere.
	/// </summary>
	/// <param name="inColor">Color of the BSphere.</param>
	void DebugView(const Vect & inColor) const override;

	/// <summary>
	/// Gets the world matrix of the BSphere
	/// </summary>
	/// <returns> The world matrix of the BSphere.</returns>
	Matrix getWorld() const;

private:
	Matrix world;
	Vect Center;
	float Radius;
};

#endif // !_CollisionVolumeBSphere