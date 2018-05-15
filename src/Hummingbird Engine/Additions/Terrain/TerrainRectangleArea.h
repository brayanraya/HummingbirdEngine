#ifndef _TerrainRectangleArea
#define _TerrainRectangleArea

#include "AzulCore.h"

class Terrain;
struct TerrainData;

/// <summary>
/// A helper class for the Terrain Iterator. Gets all the cells under an objects AABB.
/// </summary>
class TerrainRectangleArea : public Align16
{

public:
	TerrainRectangleArea() = delete;
	~TerrainRectangleArea();
	/// <summary>
	/// Initializes a new instance of the <see cref="TerrainRectangleArea"/> class. 
	/// </summary>
	/// <param name="inTerrain">The current terrain.</param>
	/// <param name="inMinPoint">The minimum point of the AABB.</param>
	/// <param name="inMaxPoint">The in maximum point of the AABB.</param>
	TerrainRectangleArea(Terrain* inTerrain, const Vect& inMinPoint, const Vect& inMaxPoint);

	/// <summary>
	/// A Debug Function that will render all the tiles below. Only used in debugging and testing. Not used in current Visualizer
	/// </summary>
	/// <param name="inMinPoint">The in minimum point.</param>
	/// <param name="inMaxPoint">The in maximum point.</param>
	void DummyTest(const Vect& inMinPoint, const Vect& inMaxPoint);

private:
	Terrain* pTerrain;
	int startCell;
	int endCell;

	int minVertical;
	int maxHorizontal;
	int maxVertical;
	int minHorizontal;

//Iterator Time
public:
	class iterator
	{
	public:
		iterator(int Index, TerrainRectangleArea* pTRA);

		/// <summary>
		/// Modifys the current cell to the next one. This will Iterate across and when it passes the max point will move down the the next row
		/// </summary>
		/// <param name="Post">The Post Increment.</param>
		/// <returns> The current Cell to be compared between iterators.</returns>
		iterator operator++(int Post);

		/// <summary>
		/// Checks to see if two iters are equal. Calls the negation of the NotEqual
		/// </summary>
		/// <param name="check">The iter to compare too.</param>
		/// <returns>True if the two are currently at the same cell.</returns>
		bool operator==(const iterator& check);
		/// <summary>
		/// Checks to see if two iters are not equal.
		/// </summary>
		/// <param name="check">The iter to compare too.</param>
		/// <returns>True if the two are currently at different cells.</returns>
		bool operator!=(const iterator& check);

		/// <summary>
		/// Gets the minimum point of the Current Cell.
		/// </summary>
		/// <returns> A Vect equal to the lowest point</returns>
		const Vect& GetMinCorner();
		/// <summary>
		/// Gets the maximum point of the Current Cell.
		/// </summary>
		/// <returns> A Vect equal to the highest point</returns>
		const Vect& GetMaxCorner();

		/// <summary>
		/// Returns the current cell we are on.
		/// </summary>
		/// <returns> The Current Cell of the iter.</returns>
		int GetCell() { return Cell; }
	private:
		TerrainRectangleArea* ptr;
		int Cell;
		int currentHorizontal;
		int currentVertical;

	};

	iterator begin()
	{
		return iterator(startCell, this);
	}

	iterator end()
	{
		return iterator(endCell, this);
	}
};

#endif // !_TerrainRectangleArea
