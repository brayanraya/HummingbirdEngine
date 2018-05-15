#ifndef _collisionTestPairCommand
#define _collisionTestPairCommand

#include "collideableGroup.h"
#include "collisionTestCommandBase.h"
#include "../../../CollisionSystem/Tools/Visualizer.h"
#include "../../../CollisionSystem/Tools/Color.h"
#include "../../../CollisionSystem/Tools/Calculations.h"
#include "../../../CollisionSystem/AABB/CollisionVolumeAABB.h"

#define VISUALIZER_ALL 1
#define VISUALIZER_AABB 0
#define VISUALIZER_BSPHERE_A 0
#define VISUALIZER_BSPHERE_B 0
#define VISUALIZER_PERSONAL 0


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Template for a given collideable testing collision against another collideable. 
///				ie. Ship against Rock.
///	</summary>
/// <remarks>	Braya, 3/1/2017. </remarks>
///
/// <typeparam name="C1">	Type of the c 1. </typeparam>
/// <typeparam name="C2">	Type of the c 2. </typeparam>
////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename C1,typename C2>
class collisionTestPairCommand: public collisionTestCommandBase
{
private:
	typename const collideableGroup<C1>::collideableCollection& Collection1;
	typename const collideableGroup<C2>::collideableCollection& Collection2;

public:
	collisionTestPairCommand():Collection1( collideableGroup<C1>::getColliderCollection() ), Collection2(collideableGroup<C2>::getColliderCollection())
	{};
	~collisionTestPairCommand()
	{
		
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Executes this object. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void execute()
	{

		const CollisionVolumeAABB* group1 = collideableGroup<C1>::getGroupsAABB();
		const CollisionVolumeAABB* group2 = collideableGroup<C2>::getGroupsAABB();

		if (Calculations::AABBCollisonTest(group1, *group2)) //check the groups
		{
#if VISUALIZER_ALL || VISUALIZER_AABB
				Visualizer::renderAABB(*group1, Color::Red);
				Visualizer::renderAABB(*group2, Color::Red); // groups collide
#endif
				for (auto it1 = Collection1.begin(); it1 != Collection1.end(); it1++)
				{
					C1* ob1 = *it1;
					const CollisionVolumeBSphere* sph1 = &ob1->GetDefaultBSphere();
					if (Calculations::bSphereCollisonTest(sph1, *group2))
					{
#if VISUALIZER_ALL || VISUALIZER_BSPHERE_A
						Visualizer::renderBSphere(*sph1,Color::Orange);
#endif
						for (auto it2 = Collection2.begin(); it2 != Collection2.end(); it2++)
						{
							C2* ob2 = *it2;
							const CollisionVolumeBSphere* sph2 = &ob2->GetDefaultBSphere();
 							if (Calculations::bSphereCollisonTest(sph1, *sph2))
							{
#if VISUALIZER_ALL || VISUALIZER_BSPHERE_B
								Visualizer::renderBSphere(*sph2, Color::Yellow);
#endif
								if (Calculations::Intersect(*it1, *it2)) //personal collision test
								{
									(*it1)->collision(*it2);
									(*it2)->collision(*it1);
#if VISUALIZER_ALL || VISUALIZER_PERSONAL
									Visualizer::showCollisionVolume(*it1, Color::Fuchsia);
									Visualizer::showCollisionVolume(*it2, Color::Fuchsia);
#endif
								}
								else
								{
#if VISUALIZER_ALL || VISUALIZER_PERSONAL
									Visualizer::showCollisionVolume(*it1);
									Visualizer::showCollisionVolume(*it2);
#endif
								}
							}
							else
							{
#if VISUALIZER_ALL || VISUALIZER_BSPHERE_B
								Visualizer::renderBSphere(*sph2);
#endif
							}
						}
					}

					else
					{
#if VISUALIZER_ALL || VISUALIZER_BSPHERE_A
						Visualizer::renderBSphere(*sph1);
#endif
					}
				}
			}
			else //no groups collide
			{
#if VISUALIZER_ALL || VISUALIZER_AABB
				Visualizer::renderAABB(*group1);
				Visualizer::renderAABB(*group2);
#endif
			}
		};

};
#endif //!_collisionTestPairCommand