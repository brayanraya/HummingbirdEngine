#ifndef _Calculations
#define _Calculations

#include "AzulCore.h"

class CollisionVolumeBoundingBox;
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class collideable;

/// <summary>
///  Static Math Functions to help make 
/// </summary>
struct Calculations
{

private:
	/// <summary>
	/// Determines if there is a Collision given 2 points and 1-2 radii.
	/// </summary>
	/// <param name="CenterPoint1">The center point1.</param>
	/// <param name="CenterPoint2">The center point2.</param>
	/// <param name="radius1">The radius1.</param>
	/// <param name="radius2">The second radius, Default = 0.</param>
	/// <returns> Returns True if there is a collision.</returns>
	static bool pointAndRadiusHelper(const Vect & CenterPoint1, const Vect & CenterPoint2, const float radius1, const float radius2 = 0);
	
	static bool SATProjectionHelper(const Vect& axisTest, const Vect& C1, const Vect& C2, const CollisionVolumeBoundingBox *box1, const CollisionVolumeBoundingBox &box2);
	
	static Vect Clamp(const Vect& toBeClamped, const Vect& Min, const Vect& Max);
	
	static Vect CenterOf2Points(const Vect& Min, const Vect& Max);
	
	static Vect Projection(const Vect & V, const Vect & W);
	
	static float LengthOfProjection(const Vect & center1, const Vect & center2, const Vect & axis);
	
	static float ClosestIntervalOnV(const Vect & inAxis, const CollisionVolumeBoundingBox& inWorld);
	
	/// <summary>
	/// Sets the minimum and maximum points of a given pointer to an AABB. *This will modify the values of the AABB*
	/// </summary>
	/// <param name="aabb">The aabb.</param>
	/// <param name="minPoint">The minimum point.</param>
	/// <param name="maxPoint">The maximum point.</param>
	static void SetAABBMinAndMax(CollisionVolumeAABB* aabb, const Vect & minPoint, const Vect & maxPoint);
	
	/// <summary>
	/// Helper Function For ABB and OBB Collisions
	/// Collison test of a boundingBox with another boundingBox.
	/// </summary>
	/// <param name="box1"> BoundingBox Parent Class.</param>
	/// <param name="box2"> BoundingBox Parent Class.</param>
	/// <returns> Returns true if there is a collision.</returns>
	static bool BoxCollisonTest(const CollisionVolumeBoundingBox * box1, const CollisionVolumeBoundingBox & box2);
public:
	static Vect minimumOf2Vect(const Vect & vect1, const Vect & vect2);
	static Vect maximumOf2Vect(const Vect & vect1, const Vect & vect2);
	static Vect GetMinFromSphere(const Vect& sphereCenter, const float& sphereRadius);
	static Vect GetMaxFromSphere(const Vect & sphereCenter, const float & sphereRadius);
	static float ScaleFromWorld(const Matrix& inMat);

	/// <summary>
	/// Bsphere collison test against another BSphere.
	/// </summary>
	/// <param name="sphere1">Sphere1.</param>
	/// <param name="sphere2">Sphere2.</param>
	/// <returns>Returns true if there is a collision.</returns>
	static bool bSphereCollisonTest(const CollisionVolumeBSphere* sphere1, const CollisionVolumeBSphere& sphere2);

	/// <summary>
	///  Bsphere collison test against another AABB.
	/// </summary>
	/// <param name="sphere1">BSphere.</param>
	/// <param name="aabb2"> AABB.</param>
	/// <returns>bool.</returns>
	static bool bSphereCollisonTest(const CollisionVolumeBSphere* sphere1, const CollisionVolumeAABB& aabb2);

	/// <summary>
	///  Bsphere collison test against another OBB.
	/// </summary>
	/// <param name="sphere1">BSphere.</param>
	/// <param name="aabb2"> OBB.</param>
	/// <returns>Returns true if there is a collision.</returns>
	static bool bSphereCollisonTest(const CollisionVolumeBSphere* sphere1, const CollisionVolumeOBB& aabb2);

	/// <summary>
	/// Collison test of AABB with BSphere. This line calls bSphereCollisionTest(bSphere,AABB). See that for refrence.
	/// </summary>
	/// <param name="aabb1">The AABB Volume</param>
	/// <param name="sphere1">The BSphere Volume</param>
	/// <returns>Returns true if there is a collision.</returns>
	static bool AABBCollisonTest(const CollisionVolumeAABB* aabb1, const CollisionVolumeBSphere& sphere1);

	/// <summary>
	///  AABB collison test against another AABB.
	/// </summary>
	/// <param name="aabb1"> The AABB.</param>
	/// <param name="sphere2">The AABB.</param>
	/// <returns>Returns true if there is a collision.</returns>
	static bool AABBCollisonTest(const CollisionVolumeAABB* aabb1, const CollisionVolumeAABB& sphere2);

	/// <summary>
	///  AABB collison test against an OBB. This line calls BoxCollisonTest(CollisionVolumeBoundingBox,CollisionVolumeBoundingBox). See that for refrence.
	/// </summary>
	/// <param name="aabb1"> The AABB.</param>
	/// <param name="sphere2">The OBB.</param>
	/// <returns>Returns true if there is a collision.</returns>
	static bool AABBCollisonTest(const CollisionVolumeAABB* aabb1, const CollisionVolumeOBB& sphere2);

	/// <summary>
	/// Collison test of OBB with BSphere. This line calls bSphereCollisionTest(bSphere,OBB). See that for refrence.
	/// </summary>
	/// <param name="obb1">The OBB.</param>
	/// <param name="sphere2">The bSphere.</param>
	/// <returns>Returns true if there is a collision.</returns>
	static bool OBBCollisonTest(const CollisionVolumeOBB* obb1, const CollisionVolumeBSphere& sphere2);

	/// <summary>
	/// Collison test of OBB with BSphere. This line calls BoxCollisonTest(CollisionVolumeBoundingBox,CollisionVolumeBoundingBox). See that for refrence.
	/// </summary>
	/// <param name="obb1"> The OBB.</param>
	/// <param name="aabb2">The AABB.</param>
	/// <returns>Returns true if there is a collision.</returns>
	static bool OBBCollisonTest(const CollisionVolumeOBB* obb1, const CollisionVolumeAABB& aabb2);

	/// <summary>
	/// Collison test of OBB with BSphere. This line calls BoxCollisonTest(CollisionVolumeBoundingBox,CollisionVolumeBoundingBox). See that for refrence.
	/// </summary>
	/// <param name="obb1"> The OBB.</param>
	/// <param name="aabb2">The OBB.</param>
	/// <returns>Returns true if there is a collision.</returns>
	static bool OBBCollisonTest(const CollisionVolumeOBB* obb1, const CollisionVolumeOBB& obb2);

	/// <summary>
	/// Double Distpatch: To call the proper CollisionTest.
	/// </summary>
	/// <param name="volume1">Collideable Volume2.</param>
	/// <param name="volume2">Collideable Volume2.</param>
	/// <returns> True, if there is an intersection between the the Collidables.</returns>
	static bool Intersect(const collideable* volume1, const collideable* volume2);
};

	

	
	

#endif //!_Calcuations
