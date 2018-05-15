#include "Calculations.h"

#include "../Bounding Sphere/CollisionVolumeBSphere.h"
#include "../AABB/CollisionVolumeAABB.h"
#include "../OBB/CollisionVolumeOBB.h"
#include "../Base Volumes/CollisionVolume.h"
#include "../../Scene Manager/Attributes/Collidable/collideable.h"

bool Calculations::pointAndRadiusHelper(const Vect& CenterPoint1, const Vect& CenterPoint2, const float radius1, const float radius2)
{
	// get distance between center points
	float distance = (CenterPoint1 - CenterPoint2).magSqr();
	// get radius distance
	float radii = radius1 + radius2;
	// test intersection
	return ((radii * radii) > distance);
}


bool Calculations::bSphereCollisonTest(const CollisionVolumeBSphere* sphere1, const CollisionVolumeBSphere& sphere2)
{
	Vect sphereCenter1 = sphere1->GetCenter();
	Vect sphereCenter2 = sphere2.GetCenter();
	float radius1 = sphere1->GetRadius();
	float radius2 = sphere2.GetRadius();

	return pointAndRadiusHelper(sphereCenter1, sphereCenter2, radius1, radius2);
}

bool Calculations::bSphereCollisonTest(const CollisionVolumeBSphere * sphere1, const CollisionVolumeAABB & aabb2)
{
	Vect sphereCenter = sphere1->GetCenter();
	float radius1 = sphere1->GetRadius();

	Vect aabbMin = aabb2.getWorldMin();
	Vect aabbMax = aabb2.getWorldMax();
	Vect clampy = Clamp(sphereCenter, aabbMin, aabbMax);

	return pointAndRadiusHelper(sphereCenter, clampy, radius1);
}

bool Calculations::bSphereCollisonTest(const CollisionVolumeBSphere * sphere1, const CollisionVolumeOBB &  obb1)
{
	Matrix inverseWorld = obb1.getWorld().getInv();

	Vect sphereWorld = sphere1->GetCenter();
	Vect sphereLocal = sphereWorld * inverseWorld;
	float radius1 = sphere1->GetRadius();

	Vect clampyLocal = Clamp(sphereLocal, obb1.getLocalMin(), obb1.getLocalMax());
	Vect clampyWorld = clampyLocal * obb1.getWorld();

	return pointAndRadiusHelper(sphereWorld, clampyWorld, radius1);
}

bool Calculations::AABBCollisonTest(const CollisionVolumeAABB * aabb2, const CollisionVolumeBSphere & sphere1)
{
	return bSphereCollisonTest(&sphere1, *aabb2);
}

bool Calculations::AABBCollisonTest(const CollisionVolumeAABB * aabb1, const CollisionVolumeAABB & aabb2)
{
	if (aabb1->getWorldMax().X() < aabb2.getWorldMin().X()) { return false; }
	if (aabb1->getWorldMin().X() > aabb2.getWorldMax().X()) { return false; }

	if (aabb1->getWorldMax().Y() < aabb2.getWorldMin().Y()) { return false; }
	if (aabb1->getWorldMin().Y() > aabb2.getWorldMax().Y()) { return false; }

	if (aabb1->getWorldMax().Z() < aabb2.getWorldMin().Z()) { return false; }
	if (aabb1->getWorldMin().Z() > aabb2.getWorldMax().Z()) { return false; }

	return true;
}

bool Calculations::AABBCollisonTest(const CollisionVolumeAABB * aabb1, const CollisionVolumeOBB & obb2)
{
	return Calculations::BoxCollisonTest(aabb1, obb2);
}

bool Calculations::OBBCollisonTest(const CollisionVolumeOBB * obb1, const CollisionVolumeBSphere & sphere2)
{
	return Calculations::bSphereCollisonTest(&sphere2, *obb1);
}

bool Calculations::OBBCollisonTest(const CollisionVolumeOBB * obb1, const CollisionVolumeAABB & aabb2)
{
	return Calculations::BoxCollisonTest(obb1, aabb2);
}

bool Calculations::SATProjectionHelper(const Vect& axisTest, const Vect& C1, const Vect& C2, const CollisionVolumeBoundingBox *box1, const CollisionVolumeBoundingBox &box2)
{
	if (axisTest.magSqr() > FLT_EPSILON)
	{
		float D = LengthOfProjection(C1, C2, axisTest);
		float Pa = ClosestIntervalOnV(axisTest, *box1);
		float Pb = ClosestIntervalOnV(axisTest, box2);
		if (D > Pa + Pb)
		{
			return false;
		};
	}
	return true;
}

bool Calculations::BoxCollisonTest(const CollisionVolumeBoundingBox * box1, const CollisionVolumeBoundingBox & box2)
{
	Vect C1 = CenterOf2Points(box1->getLocalMin(), box1->getLocalMax()) *  box1->getWorld();
	Vect C2 = CenterOf2Points(box2.getLocalMin(), box2.getLocalMax()) * box2.getWorld();

	Vect AxisTestArray[15];

	AxisTestArray[0]= box1->getWorld().get(ROW_0);
	AxisTestArray[1]= box1->getWorld().get(ROW_1);
	AxisTestArray[2]= box1->getWorld().get(ROW_2);

	AxisTestArray[3]= box2.getWorld().get(ROW_0);
	AxisTestArray[4]= box2.getWorld().get(ROW_1);
	AxisTestArray[5]= box2.getWorld().get(ROW_2);

	AxisTestArray[6]= AxisTestArray[0].cross(AxisTestArray[3]);
	AxisTestArray[7]= AxisTestArray[0].cross(AxisTestArray[4]);
	AxisTestArray[8]= AxisTestArray[0].cross(AxisTestArray[5]);

	AxisTestArray[9] =	AxisTestArray[1].cross(AxisTestArray[3]);
	AxisTestArray[10] = AxisTestArray[1].cross(AxisTestArray[4]);
	AxisTestArray[11] = AxisTestArray[1].cross(AxisTestArray[5]);

	AxisTestArray[12] = AxisTestArray[2].cross(AxisTestArray[3]);
	AxisTestArray[13] = AxisTestArray[2].cross(AxisTestArray[4]);
	AxisTestArray[14] = AxisTestArray[2].cross(AxisTestArray[5]);

	for (int i = 0; i < 15; i++)
	{
		if (!SATProjectionHelper(C1,C2, AxisTestArray[i], box1, box2)) //if false you early out.
		{
			//DebugMsg::out("Failed at %d\n", i);
			return false;
		}
	}

	return true;
}

bool Calculations::OBBCollisonTest(const CollisionVolumeOBB * obb1, const CollisionVolumeOBB & obb2)
{
	return Calculations::BoxCollisonTest(obb1, obb2);
}

bool Calculations::Intersect(const collideable * volume1, const collideable * volume2)
{
	const CollisionVolumeBoundingBox& visitor1 = volume1->GetCollisionVolume();
	const CollisionVolumeBoundingBox& visitor2 = volume2->GetCollisionVolume();

	return visitor1.Intersect(visitor2);
}

Vect Calculations::CenterOf2Points(const Vect & Min, const Vect & Max)
{
	return Vect(0.5f * (Max + Min));
}

Vect Calculations::Clamp(const Vect & toBeClamped, const Vect & Min, const Vect & Max)
{
	float x = min(Max.X(), max(toBeClamped.X(), Min.X()));
	float y = min(Max.Y(), max(toBeClamped.Y(), Min.Y()));
	float z = min(Max.Z(), max(toBeClamped.Z(), Min.Z()));
	return Vect(x,y,z);
}

Vect Calculations::Projection(const Vect & V, const Vect & W)
{
	return (((V.dot(W)) / W.dot(W))*W);
}

float Calculations::ScaleFromWorld(const Matrix & inMat)
{
	float scalx = Vect(inMat.get(ROW_0)).mag();
	float scaly = Vect(inMat.get(ROW_1)).mag();
	float scalz = Vect(inMat.get(ROW_2)).mag();
	float firstmax = max(scalx, scaly);
	float secondmax = max(firstmax, scalz);
	return secondmax;
}

float  Calculations::LengthOfProjection(const Vect& center1, const Vect& center2, const Vect& V)
{
	Vect R1 = center1 - center2;
	float temp = R1.dot(V);
	temp = fabsf(temp);
	float mag = V.magSqr();
	return temp/mag;
}

float  Calculations::ClosestIntervalOnV(const Vect& inV, const CollisionVolumeBoundingBox& inObb)
{
	Vect Vprime = inV * (inObb.getWorld().getInv());
	Vect Min = inObb.getLocalMin();
	Vect Max = inObb.getLocalMax();
	Vect dMax;

	if (Vprime.X() > 0 && Vprime.Y() > 0 && Vprime.Z() > 0) { dMax = Max;  } //+,+,+

	else if (Vprime.X() > 0 && Vprime.Y() > 0 && Vprime.Z() <= 0) { dMax = Vect(Max.X(), Max.Y(), Min.Z()); } //+,+,-

	else if (Vprime.X() > 0 && Vprime.Y() <= 0 && Vprime.Z() > 0) { dMax = Vect(Max.X(), Min.Y(), Max.Z()); } //+,-,+

	else if (Vprime.X() > 0 && Vprime.Y() <= 0 && Vprime.Z() <= 0) { dMax = Vect(Max.X(), Min.Y(), Min.Z()); } //+,-,-

	else if (Vprime.X() <= 0 && Vprime.Y() > 0 && Vprime.Z() > 0) { dMax = Vect(Min.X(), Max.Y(), Max.Z()); } //-,+,+

	else if (Vprime.X() <= 0 && Vprime.Y() > 0 && Vprime.Z() <= 0) { dMax = Vect(Max.X(), Max.Y(), Min.Z()); } //-,+,-

	else if (Vprime.X() <= 0 && Vprime.Y() <= 0 && Vprime.Z() > 0) { dMax = Vect(Min.X(), Min.Y(), Max.Z()); } //-,-,+

	else { dMax = Min; }; //-,-,-

	float ProjMax = fabsf (Vprime.X() * dMax.X()) + fabsf(Vprime.Y()* dMax.Y()) + fabsf(Vprime.Z()* dMax.Z());
	float scale = ScaleFromWorld(inObb.getWorld());
	return ((scale*scale) * ProjMax / inV.magSqr());
}

Vect Calculations::GetMinFromSphere(const Vect & sphereCenter, const float & sphereRadius)
{
	return Vect(sphereCenter.X() - sphereRadius, sphereCenter.Y() - sphereRadius, sphereCenter.Z() - sphereRadius);
}

Vect Calculations::GetMaxFromSphere(const Vect & sphereCenter, const float & sphereRadius)
{
	return Vect(sphereCenter.X() + sphereRadius, sphereCenter.Y() + sphereRadius, sphereCenter.Z() + sphereRadius);
}

void Calculations::SetAABBMinAndMax(CollisionVolumeAABB * aabb, const Vect & inMinPoint, const Vect & inMaxPoint)
{
	Vect checkMin = aabb->getWorldMin();
	Vect checkMax = aabb->getWorldMax();

	aabb->setWorldMin(minimumOf2Vect(checkMin, inMinPoint));
	aabb->setWorldMax(minimumOf2Vect(checkMin, inMaxPoint));

}

Vect Calculations::minimumOf2Vect(const Vect & vect1, const Vect & vect2)
{
	return Vect(min(vect1.X(), vect2.X()), min(vect1.Y(), vect2.Y()), min(vect1.Z(), vect2.Z()));
}

Vect Calculations::maximumOf2Vect(const Vect & vect1, const Vect & vect2)
{
	return Vect(max(vect1.X(), vect2.X()), max(vect1.Y(), vect2.Y()), max(vect1.Z(), vect2.Z()));
}