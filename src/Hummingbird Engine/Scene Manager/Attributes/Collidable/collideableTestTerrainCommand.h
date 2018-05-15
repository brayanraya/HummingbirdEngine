#ifndef _collisionTestTerrainCommand
#define _collisionTestTerrainCommand

#include "collideableGroup.h"
#include "collisionTestCommandBase.h"
#include "../../../Additions/Terrain/TerrainRectangleArea.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Template for a given collideable testing collision against another collideable. 
///				ie. Ship against Rock.
///	</summary>
/// <remarks>	Braya, 3/1/2017. </remarks>
///
/// <typeparam name="C1">	Type of the c 1. </typeparam>
/// <typeparam name="C2">	Type of the c 2. </typeparam>
////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename C1>
class collisionTestTerrainCommand: public collisionTestCommandBase
{
private:
	typename const collideableGroup<C1>::collideableCollection& Collection1;

public:
	collisionTestTerrainCommand():Collection1( collideableGroup<C1>::getColliderCollection() )
	{};
	~collisionTestTerrainCommand()
	{

	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Executes this object. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void execute()
	{
		Terrain* pTerrain = terrainManager::getCurrentTerrain();
		Vect pos;
		Vect col;
		Vect min;
		Vect max;
		float radius;
		CollisionVolumeAABB curCellAABB;


		for (auto it_mine = Collection1.begin(); it_mine != Collection1.end(); it_mine++)
		{
			pos = (*it_mine)->GetDefaultBSphere().GetCenter();
			radius = (*it_mine)->GetDefaultBSphere().GetRadius();

			min = Calculations::GetMinFromSphere(pos, radius);
			max = Calculations::GetMaxFromSphere(pos, radius);

			TerrainRectangleArea CandidateCells = TerrainRectangleArea(pTerrain, min, max);

			for (TerrainRectangleArea::iterator itCell = CandidateCells.begin(); itCell != CandidateCells.end(); itCell++)
			{
				curCellAABB.setWorldMax(itCell.GetMaxCorner());
				curCellAABB.setWorldMin(itCell.GetMinCorner());

				if (!Calculations::bSphereCollisonTest( &(*it_mine)->GetDefaultBSphere(), curCellAABB))
				{
					col = Vect(.5, 1, 1);
					//DebugMsg::out("NOT TOUCHING Ground\n");
				}
				else
				{
					if ((*it_mine)->GetCollisionVolume().Intersect(curCellAABB))
					{
						col = Vect(1, 0, 0);
						(*it_mine)->TerrainCollision();
						 //pTerrain->collision((*it_mine));
					}
					else
					{
						col = Vect(0, 0, 1);
					}
				}

				Visualizer::renderAABB(curCellAABB, col);
			}

		}
	};
};
#endif //!_collisionTestTerrainCommand