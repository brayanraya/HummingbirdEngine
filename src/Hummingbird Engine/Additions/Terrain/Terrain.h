#ifndef _Terrain
#define _Terrain

#include "../../Scene Manager/Attributes/Drawable/drawable.h"
#include "../../Scene Manager/Attributes/Collidable/collideable.h"

class GraphicsObject_TextureFlat;
class Model;
class Vect;
class EnemySoldier;


/// <summary>
/// A Struct Containing the Min and Max values for the Cells in the Terrain to generate AABBs
/// </summary>
struct TerrainData : public Align16
{
	Vect Min;
	Vect Max;
};


/// <summary>
/// Struct containing the Horizontal, Vertical and Cell Number values for the Terrain iterator.
/// </summary>
struct CellHeightAndWidth : public Align16
{
	int Horiz = 0;
	int Vert = 0;
	int Number = 0;
};

/// <summary>
/// A Class that generates terrains using a tga file height map.
/// </summary>
class Terrain : public drawable, public collideable
{
public:
	Terrain() = delete;
	/// <summary>
	/// Creates a new Terrain from the given Heightmap.
	/// </summary>
	/// <param name="heightmapFile">The heightmap file.</param>
	/// <param name="userNameOfTexture">The user name of texture.</param>
	/// <param name="size">The size.</param>
	/// <param name="RepeatU">The repeat texture u.</param>
	/// <param name="RepeatV">The repeat texture v.</param>
	Terrain(const char* heightmapFile, std::string userNameOfTexture, int size, int RepeatU, int RepeatV);
	/// <summary>
	/// A debug Function that will move change the position of the Terrain reletive to the given matrix.
	/// </summary>
	/// <param name="newPlace">The new World Matrix for the Terrain.</param>
	void move(const Matrix & newPlace);
	~Terrain();

	virtual void sceneEntry() override;
	virtual void sceneExit() override;
	virtual void draw() override;

	/// <summary>
	/// A helper function that is used to get the Horizontal Number and Vertical number of a Cell.
	/// </summary>
	/// <param name="pos">The position.</param>
	/// <returns> A CellHeightAndWidth Stuct</returns>
	CellHeightAndWidth GetOneCellBelow(const Vect & pos);
	/// <summary>
	/// A debug function that renders all the tiles in the range of the min position and max position.
	/// </summary>
	/// <param name="Min">The minimum position.</param>
	/// <param name="Max">The maximum position.</param>
	void GetAllCellsBelow(const Vect & Min, const Vect & Max);

	/// <summary>
	/// Gets the scale of the terrain.
	/// </summary>
	/// <returns>The Scale on the X,Y, and Z.</returns>
	float GetScale() { return scale; };
	/// <summary>
	/// Gets the distance between two cells.
	/// </summary>
	/// <returns>The length of a side in a cell.</returns>
	float GetDifferenceBtwPos() { return differenceToNextPos; };
	/// <summary>
	/// Gets the number of cells along the width or height.
	/// </summary>
	/// <returns>Returns the side count.</returns>
	int GetSide() { return side; };
	TerrainData* GetCells() { return cells; };
private:
	GraphicsObject_TextureFlat* pGObj_Terrain;
	Model* pModel_Terrain;
	TerrainData* cells;
	float scale;
	int side;
	float differenceToNextPos;
};

#endif //!_Terrain