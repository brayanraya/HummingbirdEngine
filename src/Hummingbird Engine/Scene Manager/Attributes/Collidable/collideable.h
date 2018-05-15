#ifndef _collideable
#define _collideable

#include "../../Game Objects/gameObjects.h"
#include "../../Scene/scene.h"
#include "../../Scene/sceneManager.h"
#include "collideableRegistratonCommand.h"
#include "collideableDeregistratonCommand.h"
#include "collideableUpdateGroupCommand.h"
#include "collideableGroup.h"

class CollisionVolumeBSphere;
class CollisionVolumeBoundingBox;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Allows inherited class to define collision with another collidable. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class collideable : public virtual gameObjects
{
public:
	enum class collideableType: char
	{
		BSPHERE,
		AABB,
		OBB,
	};

	//------------------------------------
	// Big 4. 
	//------------------------------------
	collideable();
	collideable(collideable* inCol);
	~collideable();
	const CollisionVolumeBSphere & GetDefaultBSphere() const;
	collideable(const collideable&) = delete;
	collideable& operator=(const collideable&) = delete;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Submit collideable registration. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <typeparam name="C">	Type of the c. </typeparam>
	/// <param name="inCol">	[in,out] If non-null, the in col. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename C>
	void submitCollideableRegistration(C* inCol)
	{
		assert(this->currentState == registrationState::currently_deregistered);
		pRegistrationCmd = new collideableRegistratonCommand<C>(inCol);
		pAABBUpdateCmd = new collideableUpdateGroupCommand<C>(inCol);
		sceneManager::getCurrentScene()->submitCommand(this->pRegistrationCmd);
		this->currentState = registrationState::currently_registered;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Submit collideable deregistration. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <typeparam name="C">	Type of the c. </typeparam>
	/// <param name="inCol">	[in,out] If non-null, the in col. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename C>
	void submitCollideableDeregistration(C* inCol)
	{
		assert(this->currentState == registrationState::currently_registered);
		pDeregistrationCmd = new collideableDeregistratonCommand<C>(inCol);
		sceneManager::getCurrentScene()->submitCommand(this->pDeregistrationCmd);
		this->currentState = registrationState::currently_deregistered;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Called after a collision has happened between the two types.
	///	First: User Code  - 
	/// \code
	///	userObject::userObject()
	///	 {
	///		pObject = new GraphicsObject...
	///		SetColliderModel(pToySoldier->getModel(), collideableType::AABB);
	///	 }
	/// ...
	///	void userObject::sceneEntry()
	///	 {
	///		collideable::submitCollideableRegistration<userObject>(this);
	///	 }
	/// ...
	///	void userObject::sceneExit()
	///	 {
	///		collideable::submitCollideableDeregistration<userObject>(this);
	///	 }
	/// ...
	///	void userObject::collision(otherObject *)
	///	 {
	///		//Do this when collision has happened
	///	 }
	/// ...
	///	\endcode
	///	Finally: Scene Code  - 
	/// \code
	/// ...
	///	void userScene::initialize()
	///	{
	///			tankANDSoldier = registerCollideablePair<userObject, otherObject>();
	///	}
	/// ...
	///	void userScene::sceneExit()
	///	{
	///			deregisterCollideablePair(tankANDSoldier);
	///	}
	/// ...
	///	\endcode
	/// </summary>
	/// <param name="inCol">	[in,out] If non-null, the in col. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void collision(collideable* inCol) { inCol; };

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Called after a collision has happened between the this object and the terrain.
	///	First: User Code  - 
	/// \code
	///	userObject::userObject()
	///	 {
	///		pObject = new GraphicsObject...
	///		SetColliderModel(pToySoldier->getModel(), collideableType::AABB);
	///		//if your object doesnt move call this here. Else do it in the update or when the world pos changes
	///		UpdateCollisionData(world);
	///	 }
	/// ...
	///	void userObject::sceneEntry()
	///	 {
	///		collideable::submitCollideableRegistration<userObject>(this);
	///	 }
	/// ...
	///	void userObject::sceneExit()
	///	 {
	///		collideable::submitCollideableDeregistration<userObject>(this);
	///	 }
	/// ...
	///	void userObject::TerrainCollision()
	///	 {
	///		//Do this when collision has happened
	///	 }
	/// ...
	///	\endcode
	///	Finally: Scene Code  - 
	/// \code
	/// ...
	///	void userScene::initialize()
	///	{
	///			        SetTerrain("nameOfTerrain");
	///					SetCollisionTerrain<userObject>();
	///	}
	/// ...
	///	void userScene::sceneExit()
	///	{
	///		RemoveTerrain("nameOfTerrain");
	///	}
	/// ...
	///	\endcode
	/// </summary>
	/// <param name="inCol">	[in,out] If non-null, the in col. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void TerrainCollision() {};
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets b sphere. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <returns>	The b sphere. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	const CollisionVolumeBoundingBox& GetCollisionVolume() const;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Sets collider model. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="mod">	[in,out] If non-null, the modifier. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void  SetColliderModel(Model* mod, collideableType type = collideableType::BSPHERE);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Updates the collision data. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="mat"> 	[in,out] The matrix. </param>
	/// <param name="mult">	The multiply. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void UpdateCollisionData(Matrix & mat, const float& mult);


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Updates the collision data described by mat. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="mat">	[in,out] The matrix. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void UpdateCollisionData(Matrix& mat);

	
private:
	registrationState currentState;
	commandBase* pRegistrationCmd;
	commandBase* pDeregistrationCmd;
	commandBase* pAABBUpdateCmd;
	CollisionVolumeBSphere* pColDefaultSphere;
	collideable* pCollidable;
	
	CollisionVolumeBoundingBox* pColVolume;
	Model* pModel;
};

#endif // !_collideable
