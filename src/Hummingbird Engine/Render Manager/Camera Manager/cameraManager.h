#ifndef _CameraManager
#define _CameraManager

#include "AzulCore.h"
#include <map>

class hummingbirdEngine;

///-------------------------------------------------------------------------------------------------
/// <summary>	Values that represent camera types. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
///-------------------------------------------------------------------------------------------------
enum class cameraType: char
{
	_3D,
	_2D
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Manager for cameras. Controls God Cam and Sets and Updates all cameras </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class cameraManager	//Singleton
{
private:
	//------------------------------------
	//Big 4
	//------------------------------------
	cameraManager();
	~cameraManager();
	cameraManager(const cameraManager&) = delete;
	cameraManager& operator=(const cameraManager&) = delete;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets current cameraManager singleton. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <returns>	The current cameraManager. </returns>
	///-------------------------------------------------------------------------------------------------
	static cameraManager& Instance()
	{
		if (!currentInstanceCameraManager)
			currentInstanceCameraManager = new cameraManager;
		return *currentInstanceCameraManager;
	};

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Default Cameras are automaticly loaded into the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void privateLoadDefaultCameras();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Adds provided Cameras to the map and allows that Camera to be accesssed by they key </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfCamera">	The user name of camera. </param>
	/// <param name="typeOfCamera">	   	Type of the camera. </param>
	///-------------------------------------------------------------------------------------------------
	void privateLoadCamera(std::string userNameOfCamera, cameraType typeOfCamera);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes all Cameras from the map </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void privateUnloadAllCameras();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes a specific Camera from the map </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfCamera">	The user name of camera. </param>
	///-------------------------------------------------------------------------------------------------
	void privateUnloadSpecificCamera(std::string userNameOfCamera);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets Camera pointer from map and returns it to user. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfCamera">	The user name of camera. </param>
	///
	/// <returns>	Null if it fails, else a pointer to a Camera. </returns>
	///-------------------------------------------------------------------------------------------------
	Camera* privateGetCameraFromMap(std::string userNameOfCamera);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Sets Orientation and postition of a 3D Camera </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfCamera">	The user name of camera. </param>
	/// <param name="up3DCam">		   	The up 3D camera. </param>
	/// <param name="lookAt3DCam">	   	The look at 3D camera. </param>
	/// <param name="pos3DCam">		   	The position 3D camera. </param>
	///-------------------------------------------------------------------------------------------------
	void privateSetOrientAndPosition(std::string userNameOfCamera, const Vect & up3DCam, const Vect & lookAt3DCam, const Vect & pos3DCam);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Enable God Cam </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void privateSwitchToGodCam();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Disable God Cam </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void privateSwitchOffGodCam();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Control God Cam </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void privateControlGodCam();

	//------------------------------------
	//private variables
	//------------------------------------
	/// <summary>	Manager for current instance camera. </summary>
	static cameraManager* currentInstanceCameraManager;
	/// <summary>	The current camera being used. </summary>
	Camera* currentCameraBeingUsed;
	/// <summary>	The current HUD being used. </summary>
	Camera* currentHUDBeingUsed;
	/// <summary>	The god camera. </summary>
	Camera* godCam;
	/// <summary>	The before god camera. </summary>
	Camera* beforeGodCam;
	/// <summary>	True to active. </summary>
	bool active = false;
	/// <summary>	The map of user names to pointers. </summary>
	static std::map<std::string, Camera *> mapOfUserNamesToPointers;

public:
	//------------------------------------
	//Public API
	//------------------------------------

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Default Cameras are automaticly loaded into the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	static void loadDefaultCameras() { Instance().privateLoadDefaultCameras(); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>
	/// 	Adds provided Cameras to the map and allows that Camera to be accesssed by they key The
	/// 	userNameOfCamera is the name the user will use when refering to the Camera The
	/// 	typeOfCamera is either 3D Persepctive or 2D Orthographic.
	/// </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfCamera">	The user name of camera. </param>
	/// <param name="typeOfCamera">	   	Type of the camera. </param>
	///-------------------------------------------------------------------------------------------------
	static void loadCamera(std::string userNameOfCamera, cameraType typeOfCamera) { Instance().privateLoadCamera(userNameOfCamera, typeOfCamera); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes a specific Camera from the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfCamera">	The user name of camera. </param>
	///-------------------------------------------------------------------------------------------------
	static void unloadSpecificCamera(std::string userNameOfCamera) { Instance().privateUnloadSpecificCamera(userNameOfCamera); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes all Cameras from the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	static void unloadAllCameras() { Instance().privateUnloadAllCameras(); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets Camera pointer from map and returns it to user. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfCamera">	The user name of camera. </param>
	///
	/// <returns>	Null if it fails, else the camera from map. </returns>
	///-------------------------------------------------------------------------------------------------
	static Camera* getCameraFromMap(std::string userNameOfCamera) { return Instance().privateGetCameraFromMap(userNameOfCamera); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Set the Orientation and Position of a 3D Camera. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfCamera">	The user name of camera. </param>
	/// <param name="up3DCam">		   	The up 3D camera. </param>
	/// <param name="lookAt3DCam">	   	The look at 3D camera. </param>
	/// <param name="pos3DCam">		   	The position 3D camera. </param>
	///-------------------------------------------------------------------------------------------------
	static void setOrientAndPosition(std::string userNameOfCamera, const Vect &up3DCam, const Vect & lookAt3DCam, const Vect & pos3DCam) { Instance().privateSetOrientAndPosition(userNameOfCamera, up3DCam, lookAt3DCam, pos3DCam); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Switch to god camera. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	static void switchToGodCam() { Instance().privateSwitchToGodCam(); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Switch off god camera. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	static void switchOffGodCam() { Instance().privateSwitchOffGodCam(); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Query if god camera is on. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <returns>	True if god camera on, false if not. </returns>
	///-------------------------------------------------------------------------------------------------
	static bool isGodCamOn() { return Instance().active; };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Control god camera. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	static void controlGodCam() { Instance().privateControlGodCam(); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Get Current camera. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <returns>	Null if it fails, else a pointer to current Camera. </returns>
	///-------------------------------------------------------------------------------------------------
	static Camera* currentCam() { return Instance().currentCameraBeingUsed; };

	static Camera* currentHUD() { return Instance().currentHUDBeingUsed; };

};

#endif // !_CameraManager