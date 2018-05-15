#ifndef _collideableGroup
#define _collideableGroup

#include "AzulCore.h"
#include "../../../CollisionSystem/Tools/Calculations.h"
#include "../../../CollisionSystem/Bounding Sphere/CollisionVolumeBSphere.h"
#include "collideableGroupBase.h"
#include <set>
#include <map>

class collideable;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Groups collideables of type C together. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
///
/// <typeparam name="C">	Type of the c. </typeparam>
////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename C>
class collideableGroup : public collideableGroupBase
{
public:

	using collideableCollection = std::set<C*>;
	using collideableCollectionIter = typename collideableCollection::iterator;

	//------------------------------------
	//Public API
	//------------------------------------

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Registers the collideable group described by p. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="p">	[in,out] If non-null, the C to process. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static void registerCollideableGroup(C* p) { Instance().privateRegisterCollideableGroup(p); };

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets collider collection. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <returns>	The collider collection. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static const collideableCollection& getColliderCollection() { return Instance().privateGetColliderCollection(); };

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Deregisters the collideable group described by p. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="p">	[in,out] If non-null, the C to process. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static void deregisterCollideableGroup(C* p) { Instance().privateDeregisterCollideableGroup(p); };

	static void update() { Instance().privateupdate(); };

	static const CollisionVolumeAABB* getGroupsAABB()
	{
		return Instance().privateGetGroupsAABB();
	}

	static void resetAABB(const Vect& inCenter)
	{
		Instance().privateResetAABB(inCenter);
	}
private:
	//------------------------------------
	// Big 4. 
	//------------------------------------
	collideableGroup() = default;
	~collideableGroup()
	{
		for (collideableCollection::iterator it = listOfCollidableGroups.begin(); it != listOfCollidableGroups.end(); ++it)
		{
			delete <*it>;
		};
	};
	collideableGroup(const collideableGroup&) = delete;
	collideableGroup& operator=(const collideableGroup&) = delete;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	///				 Instance creator for the singleton.
	/// </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <returns>	A reference to a collideableGroup&lt;C&gt; </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static collideableGroup<C>& Instance()
	{
		if (!currentInstanceGroup)
			currentInstanceGroup = new collideableGroup<C>;
		return *currentInstanceGroup;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="p">	[in,out] If non-null, the C to process. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void privateRegisterCollideableGroup(C* p) { quickRemove[p] = (listOfCollidableGroups.insert(p)).first; };

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Private deregister collideable group. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="p">	[in,out] If non-null, the C to process. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void privateDeregisterCollideableGroup(C* p) 
	{ 
		listOfCollidableGroups.erase(quickRemove[p]); 
		if (listOfCollidableGroups.size() == 0)
		{
			quickRemove.clear();
			groupsAABB->setWorldMax(Vect(-9999.0f, -9999.0f, -9999.0f));
			groupsAABB->setWorldMin(Vect(-9999.0f, -9999.0f, -9999.0f));
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Private get collider collection. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <returns>	A list of. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	const collideableCollection& privateGetColliderCollection() { return listOfCollidableGroups; };

	void privateupdate() 
	{
			collideableCollectionIter it = listOfCollidableGroups.begin();
			if (it != listOfCollidableGroups.end())
			{
				C* ob1 = *it;
				CollisionVolumeBSphere sph1 = ob1->GetDefaultBSphere();
				Vect tempMax = Calculations::GetMaxFromSphere(sph1.GetCenter(), sph1.GetRadius());
				Vect tempMin = Calculations::GetMinFromSphere(sph1.GetCenter(), sph1.GetRadius());

				for (it; it != listOfCollidableGroups.end(); it++)
				{
					C* ob2 = *it;
					CollisionVolumeBSphere sph2 = ob2->GetDefaultBSphere();
					Vect compMax = Calculations::GetMaxFromSphere(sph2.GetCenter(), sph2.GetRadius());
					Vect compMin = Calculations::GetMinFromSphere(sph2.GetCenter(), sph2.GetRadius());
					tempMin = Calculations::minimumOf2Vect(tempMin, compMin);
					tempMax = Calculations::maximumOf2Vect(tempMax, compMax);
				}

				groupsAABB->setWorldMax(tempMax);
				groupsAABB->setWorldMin(tempMin);
			}
	};

	const CollisionVolumeAABB* privateGetGroupsAABB()
	{
		return groupsAABB;
	};

	//------------------------------------
	//private variables
	//------------------------------------
	static collideableGroup<C>* currentInstanceGroup;
	collideableCollection listOfCollidableGroups;
	std::map<collideable*, collideableCollectionIter> quickRemove;
};

template<typename C>
collideableGroup<C>* collideableGroup<C>::currentInstanceGroup = nullptr;
#endif _collideableGroup


