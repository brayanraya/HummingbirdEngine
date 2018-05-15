#include "collideable.h"
#include "../../../CollisionSystem/Bounding Sphere/CollisionVolumeBSphere.h"
#include "../../../CollisionSystem/AABB/CollisionVolumeAABB.h"
#include "../../../CollisionSystem/OBB/CollisionVolumeOBB.h"
#include "collideableGroup.h"

collideable::collideable()
{
	currentState = registrationState::currently_deregistered;
	pRegistrationCmd = nullptr;
	pDeregistrationCmd = nullptr;
	pCollidable = nullptr;
	pColVolume = nullptr;
	pModel = nullptr;
	pColDefaultSphere = new CollisionVolumeBSphere;
}

collideable::collideable(collideable * inCol): pCollidable(inCol)
{
}

collideable::~collideable()
{
	delete pColDefaultSphere;

	if (pRegistrationCmd != nullptr)
	{
		delete pRegistrationCmd;
	}
	if (pDeregistrationCmd != nullptr)
	{
		delete pDeregistrationCmd;
	}
	if (pCollidable != nullptr)
	{
		delete pCollidable;
	}
}

const CollisionVolumeBSphere& collideable::GetDefaultBSphere() const
{
	return *pColDefaultSphere;
}

const CollisionVolumeBoundingBox& collideable::GetCollisionVolume() const
{
	return *pColVolume;
}

void collideable::SetColliderModel(Model * mod, collideableType type)
{
	pModel = mod;

	switch (type)
	{
	case collideable::collideableType::BSPHERE:
		pColVolume = (CollisionVolumeBoundingBox*) pColDefaultSphere;
		break;
	case collideable::collideableType::AABB:
		pColVolume = (CollisionVolumeBoundingBox*) new CollisionVolumeAABB;
		break;
	case collideable::collideableType::OBB:
		pColVolume = (CollisionVolumeBoundingBox*) new CollisionVolumeOBB;
		break;
	default:
		assert(false && "I'm not sure how you got here, I used Enums. So either you're stupid or i am");
		pColVolume = nullptr;
		break;
	}
}

void collideable::UpdateCollisionData(Matrix & mat)
{
	pColDefaultSphere->ComputeData(pModel, mat);
	pColVolume->ComputeData(pModel, mat);

	sceneManager::getCurrentScene()->submitCommand(this->pAABBUpdateCmd);
}

void collideable::UpdateCollisionData(Matrix & mat, const float& mult)
{
	pColDefaultSphere->ComputeData(pModel, mat, mult);
	pColVolume->ComputeData(pModel, mat, mult);
}
