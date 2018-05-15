#include "TerrainRectangleArea.h"

#include "Terrain.h"
#include "AzulCore.h"

TerrainRectangleArea::~TerrainRectangleArea()
{
}

TerrainRectangleArea::TerrainRectangleArea(Terrain* inTerrain, const Vect & inMinPoint, const Vect & inMaxPoint)
{
	pTerrain = inTerrain;

	int side = inTerrain->GetSide();

	CellHeightAndWidth mini = inTerrain->GetOneCellBelow(inMinPoint);
	CellHeightAndWidth maxi = inTerrain->GetOneCellBelow(inMaxPoint);

	minVertical = min(mini.Vert, maxi.Vert);
	minHorizontal = min(mini.Horiz, maxi.Horiz);

	maxVertical = max(mini.Vert, maxi.Vert);
	maxHorizontal = max(mini.Horiz, maxi.Horiz);

	startCell = ((minHorizontal*(side - 1)) * 2) + 2 + (minVertical * 2);
	endCell = ((maxHorizontal*(side - 1)) * 2) + 2 + (maxVertical * 2)+1;
}

void TerrainRectangleArea::DummyTest(const Vect & inMinPoint, const Vect & inMaxPoint)
{
	pTerrain->GetAllCellsBelow(inMinPoint, inMaxPoint);
}

TerrainRectangleArea::iterator::iterator(int Index, TerrainRectangleArea * pTRA)
{
	Cell = Index;
	currentHorizontal = pTRA->minHorizontal;
	currentVertical = pTRA->minVertical;
	ptr = pTRA;
}

TerrainRectangleArea::iterator TerrainRectangleArea::iterator::operator++(int)
{
	currentVertical++;
	if (currentVertical > ptr->maxVertical)
	{
		currentVertical = ptr->minVertical;
		currentHorizontal++;
	}

	Cell = ((currentHorizontal*(ptr->pTerrain->GetSide() - 1)) * 2) + 2 + (currentVertical * 2);

	return *this;
}

bool TerrainRectangleArea::iterator::operator==(const iterator & check)
{
	return (this->Cell == check.Cell);
}

bool TerrainRectangleArea::iterator::operator!=(const iterator & check)
{
	return (this->Cell <= check.Cell);
}

const Vect & TerrainRectangleArea::iterator::GetMinCorner()
{
	return (ptr->pTerrain->GetCells())[Cell].Min;
}

const Vect & TerrainRectangleArea::iterator::GetMaxCorner()
{
	return (ptr->pTerrain->GetCells())[Cell].Max;
}
