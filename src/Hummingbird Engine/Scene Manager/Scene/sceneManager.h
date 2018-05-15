#ifndef _sceneManager
#define _sceneManager

class scene;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Manages the current scene and next scene for quick switching. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class sceneManager // singlton
{
private:
	//------------------------------------
	//Big 4
	//------------------------------------
	sceneManager() = default;
	~sceneManager();
	sceneManager(const sceneManager&) = delete;
	sceneManager& operator=(const sceneManager&) = delete;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Instance creator for the singleton. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <returns>	The current sceneManager. </returns>
	///-------------------------------------------------------------------------------------------------
	static sceneManager& Instance()
	{
		if (!currentInstanceSceneManager)
			currentInstanceSceneManager = new sceneManager;
		return *currentInstanceSceneManager;
	};

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Private function: Swaps Scenes. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void privSwapScenes();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Private function: Sets start scene. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <param name="inputScene">	Scene to become the Start. </param>
	///-------------------------------------------------------------------------------------------------
	void privSetStartScene(scene* inputScene);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Private function: Change current scene. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <param name="inputScene">	The input scene. </param>
	///-------------------------------------------------------------------------------------------------
	void privChangeCurrentScene(scene* inputScene);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Private function: End all scenes. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void privEndAllScenes();

	void privEndCurrentScene();

	/// <summary>	current instance of SceneManager. </summary>
	static sceneManager* currentInstanceSceneManager;

	/// <summary>	The current scene managed. </summary>
	scene* currentSceneManaged = nullptr;
	
	/// <summary>	The next scene manged. </summary>
	scene* nextSceneManged = nullptr;

public:

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets start scene. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <param name="inputScene">	The next current scene. </param>
	///-------------------------------------------------------------------------------------------------
	static void setStartScene(scene* inputScene) { Instance().privSetStartScene(inputScene); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Change current scene to the one passed in. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <param name="inputScene">	The Next current scene. </param>
	///-------------------------------------------------------------------------------------------------
	static void changeCurrentScene(scene* inputScene) { Instance().privChangeCurrentScene(inputScene); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Swap scenes. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	static void swapScenes() { Instance().privSwapScenes(); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets current scene. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <returns>	The current scene. </returns>
	///-------------------------------------------------------------------------------------------------
	static scene* getCurrentScene() { return Instance().currentSceneManaged; };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Ends all scenes. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	static void endAllScenes() { Instance().privEndAllScenes(); };

	static void endCurrrentScene() { Instance().privEndCurrentScene(); };
};

#endif // !_sceneManager