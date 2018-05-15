#include "Terrain.h"

#include <assert.h>

#include "AzulCore.h"
#include "TextureTGA.h"
#include "GpuVertTypes.h"
#include "../../Asset Manager/Shader Manger/shaderManager.h"
#include "../../Asset Manager/Texture Manager/textureManager.h"
#include "../../Render Manager/Camera Manager/cameraManager.h"

#include "../../CollisionSystem/Tools/Visualizer.h"

#include <string>

Terrain::Terrain(const char* heightmapFile, std::string userNameOfTexture, int size, int RepeatU, int RepeatV) //just filename and extension
{
	scale = (float)size;

	GLint imgWidth, imgHeigth, icomp;	//last does not matter
	GLenum dtype;						//does not matter
	GLbyte* imgData = gltReadTGABits(heightmapFile, &imgWidth, &imgHeigth, &icomp, &dtype);
	assert(imgWidth == imgHeigth && imgWidth != 0); // We need square images for heightmaps
	
	side = imgHeigth;	// the image should be square
	const unsigned int pixel_width = 3;			// 4 bytes RGBA per pixel

	//char Pixel = imgData[0 * pixel_width];// gets R value
	//(void)Pixel;

	int nverts = side*side;
	VertexStride_VUN *pVerts = new VertexStride_VUN[nverts];
	int ntri = (side - 1) * (side - 1) * 2;
	TriangleIndex *pTriList = new TriangleIndex[ntri];

	differenceToNextPos = 1 / float(side - 1);
	int place = 0;
	for ( int i = 0; i < side; i++)
	{
		for ( int j = 0; j < side; j++)
		{
			float xPosition = (-0.5f + (differenceToNextPos * j)) * (float)size;
			unsigned char Pixel = imgData[pixel_width * (int(j) * side + int(i))];
			float yPosition = (((float(Pixel) / 255.0f)*0.5f)*(float)size) - ((2 * (size / 10)) + ((size / 10) / 2)); //minus to make the world centered around 0,0,0,
			float zPosition = (0.5f - (differenceToNextPos * i))*(float)size;
			float uMap = (differenceToNextPos * float(i))* float(RepeatU);
			float vMap = (differenceToNextPos *  float(j))* float(RepeatV);
			pVerts[place].set(xPosition, yPosition, zPosition, uMap, vMap,0,0,0);
			place++;
		}
	}

	cells = new TerrainData[ntri];
	place = 0;
	for ( int i = 0; i < side - 1; i++)
	{
		for ( int j = 0; j < side - 1; j++)
		{
			pTriList[place].set((i*side) + j + 1, (((i + 1) * side) + j), ((i*side) + j)); // top triangle
			pTriList[place + 1].set((((i + 1) * side) + j) + 1, (((i + 1) * side) + j), i*side + j + 1); // bottom tiangle

			//Get the first 2 points (x)
			//	x--------x  
			//	|        |
			//  |        |
			//  .--------.
			VertexStride_VUN VertexA = pVerts[(i*side) + j + 1];
			VertexStride_VUN VertexB = pVerts[(((i + 1) * side) + j)];

			Vect vtemp1 = Vect(VertexA.x, VertexA.y, VertexA.z);
			Vect vtemp2 = Vect(VertexB.x, VertexB.y, VertexB.z);

			Vect vtempMin(Calculations::minimumOf2Vect(vtemp1, vtemp2));
			Vect vtempMax(Calculations::maximumOf2Vect(vtemp1, vtemp2));

			//Get the first 2 points (x)
			//	x--------.  
			//	|        |
			//  |        |
			//  x--------.

			VertexB = pVerts[((i*side) + j)];
			vtemp2 = Vect(VertexB.x, VertexB.y, VertexB.z);

			vtempMin = Calculations::minimumOf2Vect(vtempMin, vtemp2);
			vtempMax = Calculations::maximumOf2Vect(vtempMax, vtemp2);

			//Get the first 2 points (x)
			//	x--------.  
			//	|        |
			//  |        |
			//  .--------x

			VertexB = pVerts[(((i + 1) * side) + j) + 1];
			vtemp2 = Vect(VertexB.x, VertexB.y, VertexB.z);

			vtempMin = Calculations::minimumOf2Vect(vtempMin, vtemp2);
			vtempMax = Calculations::maximumOf2Vect(vtempMax, vtemp2);

			cells[place].Max = vtempMax;
			cells[place].Min = vtempMin;

			place += 2;
		}
	}
	pModel_Terrain = new Model(pVerts, nverts, pTriList, ntri);
	pGObj_Terrain = new GraphicsObject_TextureFlat(pModel_Terrain, shaderManager::getShaderFromMap("pShaderObject_texture"), textureManager::getTextureFromMap(userNameOfTexture));

	//delete verts and triangle list
	delete[] pVerts;
	delete[] pTriList;

	SetColliderModel(pModel_Terrain);
}


void Terrain::move(const Matrix& newPlace)
{
	Matrix temp = newPlace;
	pGObj_Terrain->SetWorld(temp);
}

Terrain::~Terrain()
{
	delete pGObj_Terrain;
	delete pModel_Terrain;
}

void Terrain::sceneEntry()
{
	drawable::submitDrawableRegistration();
	collideable::submitCollideableRegistration<Terrain>(this);
	Matrix World(IDENTITY);
	UpdateCollisionData(World);
}

void Terrain::sceneExit()
{
	drawable::submitDrawableDeregistration();
	collideable::submitCollideableDeregistration<Terrain>(this);
}
void Terrain::draw()
{
	pGObj_Terrain->Render(cameraManager::currentCam());

	//for (int i = 0; i < (side - 1) * (side - 1) * 2; i++)
	//{
	//	CollisionVolumeAABB temp;
	//	temp.setWorldMax(cells[i].Max);
	//	temp.setWorldMin(cells[i].Min);
	//	Visualizer::renderAABB(temp, Color::Blue);
	//}
}

CellHeightAndWidth Terrain::GetOneCellBelow(const Vect& pos)
{
	int Vertical = (int)(((pos.X() / scale) + 0.5f) / differenceToNextPos) - 1;
	int Horizontal = (int)((-(pos.Z() / scale) + 0.5f) / differenceToNextPos);

	int cellNumber = 0;

	CellHeightAndWidth returnCell;

	if (Horizontal >= 0 && Vertical >= 0 && Horizontal < side - 2 && Vertical < side - 2)
	{
		cellNumber = ((Horizontal*(side - 1)) * 2) + 2 + (Vertical * 2);
		returnCell.Horiz = Horizontal;
		returnCell.Vert = Vertical;
		returnCell.Number = cellNumber;

		/*if (Horizontal >= 0 && Vertical >= 0 && Horizontal < side - 2 && Vertical < side - 2)
		{
			CollisionVolumeAABB temp;
			temp.setWorldMax(cells[cellNumber].Max);
			temp.setWorldMin(cells[cellNumber].Min);
			Visualizer::renderAABB(temp, Color::Firebrick);
		}*/
	}
	return returnCell;
}

void Terrain::GetAllCellsBelow(const Vect& Min, const Vect& Max)
{
	int minVertical = (int)(((Min.X() / scale) + 0.5f) / differenceToNextPos) - 1;
	int minHorizontal = (int)((-(Min.Z() / scale) + 0.5f) / differenceToNextPos);

	int maxVertical = (int)(((Max.X() / scale) + 0.5f) / differenceToNextPos) - 1;
	int maxHorizontal = (int)((-(Max.Z() / scale) + 0.5f) / differenceToNextPos);

	int Horizontal = maxHorizontal;
	int Vertical = minVertical;

	int width =(minHorizontal - maxHorizontal);
	int height = (maxVertical - minVertical) +1;

	for (int i = 0; i <= ((width*height)+ height)-1; i++)
	{
		if (Horizontal >= 0 && Vertical >= 0 && Horizontal < side - 1 && Vertical < side - 1)
		{
			CollisionVolumeAABB temp;
			temp.setWorldMax(cells[((Horizontal*(side - 1)) * 2) + 2 + (Vertical * 2)].Max);
			temp.setWorldMin(cells[(((Horizontal*(side - 1)) * 2) + 2 + (Vertical * 2))].Min);
			Visualizer::renderAABB(temp, Color::Firebrick);
		}
		Horizontal++;
		if (Horizontal == minHorizontal+1)
		{
			Horizontal = maxHorizontal;
			Vertical++;
		}
	}
}