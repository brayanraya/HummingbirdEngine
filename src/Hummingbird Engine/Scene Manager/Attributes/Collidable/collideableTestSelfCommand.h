#ifndef _collisionTestSelfCommand
#define _collisionTestSelfCommand

#include "collideableGroup.h"
#include "collisionTestCommandBase.h"
#include "../../../CollisionSystem/Tools/Visualizer.h"
#include "../../../CollisionSystem/Tools/Color.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Template for a given collideable testing collision against another collideable of the same type.
/// 			ie. Ship against Ship.
/// </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
///
/// <typeparam name="C1">	Type of the c 1. </typeparam>
////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename C1>
class collisionTestSelfCommand: public collisionTestCommandBase
{
private:
	typename const collideableGroup<C1>::collideableCollection& Collection1;

public:
	collisionTestSelfCommand():Collection1( collideableGroup<C1>::getColliderCollection() )
	{};
	~collisionTestSelfCommand()
	{

	};

	void execute()
	{
		for (auto it1 = Collection1.begin(); it1 != Collection1.end(); it1++)
		{
			const CollisionVolumeBSphere& bs1 = (*it1)->GetBSphere();

			bool test_result = (*it1)->pBSphere.Intersect((*it2)->pBSphere);
			if (test_result)
			{
				(*it1)->collision(*it1);
				Visualizer::renderBSphere(bs1, Color::Red);
			}
			else
			{
				Visualizer::renderBSphere(bs1, Color::Blue);
			}
		}
	};

};
#endif // !_collisionTestSelfCommand