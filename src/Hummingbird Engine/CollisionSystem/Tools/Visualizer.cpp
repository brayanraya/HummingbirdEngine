#include "Visualizer.h"
#include "GraphicsObject_WireframeConstantColor.h"

#include "../Bounding Sphere/CollisionVolumeBSphere.h"
#include "../AABB/CollisionVolumeAABB.h"
#include "../OBB/CollisionVolumeOBB.h"

#include "../../Render Manager/Camera Manager/cameraManager.h"
#include "../../Scene Manager/Attributes/Collidable/collideable.h"

const Vect Visualizer::DefaultColor = Color::Blue;
Visualizer* Visualizer::currentInstanceVisualizer = nullptr;

Visualizer::Visualizer()
{
	Vect Red(DefaultColor);
	WFUnitSphere = new GraphicsObject_WireframeConstantColor(modelManager::getModelFromMap("azulDefaultSphere"), shaderManager::getShaderFromMap("pShaderObject_constantColor"), Red);
	WFUnitBox = new GraphicsObject_WireframeConstantColor(modelManager::getModelFromMap("azulDefaultBox"), shaderManager::getShaderFromMap("pShaderObject_constantColor"), Red);
}

Visualizer::~Visualizer()
{
	delete WFUnitSphere;
	delete WFUnitBox;
}

void Visualizer::privRenderBSphere(Matrix & S, const Vect & col)
{
	visualizerData temp(S,col);
	if (col.isEqual(DefaultColor))
	{
		listofSpheresNotCollide.push_back(temp);
	}
	else
	{
		listofSpheresCollide.push_back(temp);
	}
}

void Visualizer::privRenderAABB(Matrix & S, const Vect & col)
{
	visualizerData temp(S, col);
	if (col.isEqual(DefaultColor))
	{
		listofBoxesNotCollide.push_back(temp);
	}
	else
	{
		listofBoxesCollide.push_back(temp);
	}
}

void Visualizer::privShowCollisionVolume(const collideable* inCollideable, const Vect & col) const
{
	inCollideable->GetCollisionVolume().DebugView(col);
}

void Visualizer::privRenderAll()
{
	std::list<visualizerData>::iterator start;
	std::list<visualizerData>::iterator end;

	start = listofSpheresNotCollide.begin();
	end = listofSpheresNotCollide.end();

	//First print those that dont collide
	//Sphere first

	while (start != end)
	{
		WFUnitSphere->pWireColor->set((*start).Color);
		WFUnitSphere->SetWorld((*start).location);
		WFUnitSphere->Render(cameraManager::currentCam());
		start++;
		listofSpheresNotCollide.pop_front();
	}

	//aabb next
	start = listofBoxesNotCollide.begin();
	end = listofBoxesNotCollide.end();

	while (start != end)
	{
		WFUnitBox->pWireColor->set((*start).Color);
		WFUnitBox->SetWorld((*start).location);
		WFUnitBox->Render(cameraManager::currentCam());
		start++;
		listofBoxesNotCollide.pop_front();
	}

	start = listofSpheresCollide.begin();
	end = listofSpheresCollide.end();

	while (start != end)
	{
		WFUnitSphere->pWireColor->set((*start).Color);
		WFUnitSphere->SetWorld((*start).location);
		WFUnitSphere->Render(cameraManager::currentCam());
		start++;
		listofSpheresCollide.pop_front();
	}


	start = listofBoxesCollide.begin();
	end = listofBoxesCollide.end();

	while (start != end)
	{
		WFUnitBox->pWireColor->set((*start).Color);
		WFUnitBox->SetWorld((*start).location);
		WFUnitBox->Render(cameraManager::currentCam());
		start++;
		listofBoxesCollide.pop_front();
	}
}

void Visualizer::renderBSphere(const CollisionVolumeBSphere & S, const Vect & col)
{
	float scale = S.GetRadius();
	Matrix location = Matrix(SCALE,scale,scale,scale) *  Matrix(TRANS, S.GetCenter()) ;
	Instance().privRenderBSphere(location, col);
}

void Visualizer::renderAABB(const CollisionVolumeAABB & S, const Vect & col)
{
	Vect Max = S.getWorldMax();
	Vect Min = S.getWorldMin();
	Vect size = Max - Min;
	Vect pos = (0.5f * (Max + Min));
	Matrix location = Matrix(SCALE, size) * Matrix(TRANS, pos);
	Instance().privRenderAABB(location,col);
}

void Visualizer::renderOBB(const CollisionVolumeOBB & S, const Vect & col)
{
	Vect Max = S.getLocalMax();
	Vect Min = S.getLocalMin();
	Vect size = Max - Min;
	Vect pos = (0.5f * (Max + Min));
	Matrix localSpace = Matrix(SCALE, size) * Matrix(TRANS, pos);
	localSpace *= S.getWorld();
	Instance().privRenderAABB(localSpace, col);
}

void Visualizer::showCollisionVolume(const collideable* inCollideable, const Vect & col)
{
	Instance().privShowCollisionVolume(inCollideable,col);
}