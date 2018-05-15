#ifndef _Visualizer
#define _Visualizer
#include "AzulCore.h"
#include "Color.h"
#include "../../Asset Manager/Model Manger/modelManager.h"
#include "../../Asset Manager/Shader Manger/shaderManager.h"

#include <list>

class collideable;
class CollisionVolumeAABB;
class CollisionVolumeBSphere;
class CollisionVolumeOBB;

/// <summary>
/// A struct constaining Location and Color for our Visualizer to place the BSpheres and 
/// AABBs in the correct place and color.
/// </summary>
struct visualizerData
{
	visualizerData(const Matrix& inMat, const Vect& inVec) { location = inMat; Color = inVec; };
	~visualizerData() {};

	Matrix location;
	Vect Color;
};

/// <summary>
/// SINGLETON:
/// A debugging tool for seeing collidable areas. 
/// </summary>
class Visualizer: public Align16
{
private:
	//------------------------------------
	//Big 4
	//------------------------------------

	Visualizer();
	~Visualizer();
	Visualizer(const Visualizer&) = delete;
	Visualizer& operator=(const Visualizer&) = delete;

	//------------------------------------
	//Private Variables
	//------------------------------------

	/// <summary>	Instance creator for the singleton. </summary>
	///
	/// <remarks>	Braya, 3/2/2017. </remarks>
	///
	/// <returns>	A reference to a Visualizer. </returns>
	static Visualizer& Instance()
	{
		if (!currentInstanceVisualizer)
			currentInstanceVisualizer = new Visualizer;
		return *currentInstanceVisualizer;
	};

	/// <summary> 
	/// Adds the Bsphere information into a visualizerData and places it into the appropriate 
	/// Queue to be rendered later.
	/// </summary>
	/// <param name="S">    The Position in World Space. </param>
	/// <param name="col">	The color. </param>
	void privRenderBSphere(Matrix& S, const Vect& col);

	/// <summary> 
	/// Adds the Bsphere information into a visualizerData and places it into the appropriate 
	/// Queue to be rendered later.
	/// </summary>
	/// <param name="S">    The Position in World Space. </param>
	/// <param name="col">	The color. </param>
	void privRenderAABB(Matrix& S, const Vect& col);

	/// <summary>
	/// Double Dispatch:
	/// Used to call renderBSphere/renderAABB/renderOVBB below. 
	/// </summary>
	/// <param name="inCollideable">The in collideable.</param>
	/// <param name="col">The col.</param>
	void privShowCollisionVolume(const collideable* inCollideable, const Vect & col) const;

	/// <summary>  Pops all data from all queues and renders visual volumes to the Screen. </summary>
	void privRenderAll();

	//------------------------------------
	//private variables
	//------------------------------------
	static Visualizer* currentInstanceVisualizer;
	static const Vect DefaultColor;
	GraphicsObject_WireframeConstantColor* WFUnitSphere;
	GraphicsObject_WireframeConstantColor* WFUnitBox;

	std::list<visualizerData> listofSpheresCollide;
	std::list<visualizerData> listofSpheresNotCollide;
	std::list<visualizerData> listofBoxesCollide;
	std::list<visualizerData> listofBoxesNotCollide;

public:
	//------------------------------------
	//Public API
	//------------------------------------

	/// <summary>  Prepares a bSpheres data to be placed in a queue for printing. </summary>
	/// <param name="S">The BSphere.</param>
	/// <param name="col">The Color.</param>
	static void renderBSphere(const CollisionVolumeBSphere& S, const Vect& col = DefaultColor);
	/// <summary>  Prepares a AABB data to be placed in a queue for printing. </summary>
	/// <param name="S">The AABB.</param>
	/// <param name="col">The Color.</param>
	static void renderAABB(const CollisionVolumeAABB& S, const Vect& col = DefaultColor);
	/// <summary>  Prepares a OBB data to be placed in a queue for printing. </summary>
	/// <param name="S">The OBB.</param>
	/// <param name="col">The Color.</param>
	static void renderOBB(const CollisionVolumeOBB& S, const Vect& col = DefaultColor);

	/// <summary> 
	/// Double Dispatch:
	/// Prepares a Collidable of unknown type to be placed in a queue for later Rendering. 
	/// </summary>
	/// <param name="S">The OBB.</param>
	/// <param name="col">The Color.</param>
	static void showCollisionVolume(const collideable* inCollideable, const Vect& col = DefaultColor);
	
	/// <summary>  Pops all data from all queues and renders visual volumes to the Screen. </summary>
	static void renderAll() { Instance().privRenderAll(); };
};

#endif // !_Visualizer