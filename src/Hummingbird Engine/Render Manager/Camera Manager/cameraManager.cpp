#include "CameraManager.h"
#include "../../Main Game/hummingbirdEngine.h"

cameraManager* cameraManager::currentInstanceCameraManager = nullptr;
std::map<std::string, Camera*> cameraManager::mapOfUserNamesToPointers;

///for God camera
Vect CamPos(50, 50, 100.0f);
Matrix CamRot(IDENTITY);		// No rotation initially
Vect CamUp(0, 1, 0);			// Using local Y axis as 'Up'
Vect CamDir(0, 0, 1);			// Using the local Z axis as 'forward'
const float CamTranSpeed = 2;
const float CamRotSpeed = .02f;

void cameraManager::privateLoadDefaultCameras()
{
	//DebugMsg::out("\nLoading Default Cameras\n");
	cameraManager::loadCamera("default3D", cameraType::_3D);
	mapOfUserNamesToPointers["default3D"]->setViewport(0, 0, hummingbirdEngine::getWindowWidth(), hummingbirdEngine::getWindowHeight());
	mapOfUserNamesToPointers["default3D"]->setPerspective(35.0f, float(hummingbirdEngine::getWindowWidth()) / float(hummingbirdEngine::getWindowHeight()), 1.0f, 5000.0f);

	cameraManager::loadCamera("default2D", cameraType::_2D);
	mapOfUserNamesToPointers["default2D"]->setViewport(0, 0, hummingbirdEngine::getWindowWidth(), hummingbirdEngine::getWindowHeight());
	mapOfUserNamesToPointers["default2D"]->setOrthographic(-0.5f*hummingbirdEngine::getWindowWidth(), 0.5f*hummingbirdEngine::getWindowWidth(), -0.5f*hummingbirdEngine::getWindowHeight(), 0.5f*hummingbirdEngine::getWindowHeight(), 1.0f, 1000.0f);

	cameraManager::setOrientAndPosition("default3D", Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, 0.0f), Vect(50.0f, 50.0f, 150.0f));
	cameraManager::setOrientAndPosition("default2D", Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, -1.0f), Vect(0.0f, 0.0f, 0.0f));

	currentCameraBeingUsed = mapOfUserNamesToPointers["default3D"];
	currentHUDBeingUsed = mapOfUserNamesToPointers["default2D"];
}

void cameraManager::privateLoadCamera(std::string userNameOfCamera, cameraType typeOfCamera)
{
	//DebugMsg::out("Loading Camera: %s", userNameOfCamera.c_str());
	if (mapOfUserNamesToPointers[userNameOfCamera] == nullptr)
	{
		if (typeOfCamera == cameraType::_3D)
		{
			mapOfUserNamesToPointers[userNameOfCamera] = new Camera(Camera::Type::PERSPECTIVE_3D);
		}
		else
		{
			mapOfUserNamesToPointers[userNameOfCamera] = new Camera(Camera::Type::ORTHOGRAPHIC_2D);
		}
	}
	else
	{
		//DebugMsg::out("->Failed\n");
		assert(false && "This name is already being used by another Camera");
	}
	//DebugMsg::out("->Success\n");
}

void cameraManager::privateUnloadSpecificCamera(std::string userNameOfCamera)
{
	//DebugMsg::out("\nDeleting Camera: %s\n", userNameOfCamera.c_str());
	//first delete the news
	delete mapOfUserNamesToPointers[userNameOfCamera];
	//then remove from the map
	mapOfUserNamesToPointers.erase(userNameOfCamera);
}

void cameraManager::privateUnloadAllCameras()
{
	//DebugMsg::out("\nDeleting All Cameras\n");
	//delete all Camera pointers individually
	for (std::map<std::string, Camera*>::iterator it = mapOfUserNamesToPointers.begin(); it != mapOfUserNamesToPointers.end(); ++it)
	{
		//DebugMsg::out("Deleting Camera: %s\n", it->first.c_str());
		delete it->second;
	}
	//Then clear the map
	mapOfUserNamesToPointers.clear();
	//final delete manager
	delete currentInstanceCameraManager;
	currentInstanceCameraManager = nullptr;
}

Camera * cameraManager::privateGetCameraFromMap(std::string userNameOfCamera)
{
	return mapOfUserNamesToPointers[userNameOfCamera];
}

void cameraManager::privateSetOrientAndPosition(std::string userNameOfCamera, const Vect & up3DCam, const Vect & lookAt3DCam, const Vect & pos3DCam)
{
	mapOfUserNamesToPointers[userNameOfCamera]->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
	//Update camera every time it moves!
	mapOfUserNamesToPointers[userNameOfCamera]->updateCamera();
}

void cameraManager::privateSwitchToGodCam()
{
	beforeGodCam = currentCameraBeingUsed;
	currentCameraBeingUsed = godCam;
	active = true;
}

void cameraManager::privateSwitchOffGodCam()
{
	currentCameraBeingUsed = beforeGodCam;
	beforeGodCam = nullptr;
	active = false;
}

void cameraManager::privateControlGodCam()
{
	// Camera translation movement (NOTE: This time, I'm NOT using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_I))
	{
		CamPos += Vect(0, 0, 1) * CamRot * CamTranSpeed;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_K))
	{
		CamPos += Vect(0, 0, 1) * CamRot * -CamTranSpeed;
	}

	if (Keyboard::GetKeyState(AZUL_KEY::KEY_J))
	{
		CamPos += Vect(1, 0, 0) * CamRot * CamTranSpeed;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_L))
	{
		CamPos += Vect(1, 0, 0) * CamRot * -CamTranSpeed;
	}

	// Camera Rotation movement (NOTE: This time, I'm NOT using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_LEFT))
	{
		CamRot *= Matrix(ROT_Y, CamRotSpeed);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_RIGHT))
	{
		CamRot *= Matrix(ROT_Y, -CamRotSpeed);
	}

	if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_UP))
	{
		CamRot *= Matrix(ROT_AXIS_ANGLE, Vect(1, 0, 0) * CamRot, -CamRotSpeed);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_DOWN))
	{
		CamRot *= Matrix(ROT_AXIS_ANGLE, Vect(1, 0, 0) * CamRot, CamRotSpeed);
	}

	// Update the camera settings
	godCam->setOrientAndPosition(CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
	godCam->updateCamera();
}

cameraManager::cameraManager()
{
	{
		godCam = new Camera(Camera::Type::PERSPECTIVE_3D);
		godCam->setViewport(0, 0, hummingbirdEngine::getWindowWidth(), hummingbirdEngine::getWindowHeight());
		godCam->setPerspective(35.0f, float(hummingbirdEngine::getWindowWidth()) / float(hummingbirdEngine::getWindowHeight()), 1.0f, 5000.0f);
		// Position and Orient Camera
		//      First: we create a rotation matrix pointing (Z) towards the target
		Vect Target(0, 0, 0);
		CamRot.set(ROT_ORIENT, Target - CamPos, CamUp);

		//		Second: we set the camera to its position and pointing toward the target
		godCam->setOrientAndPosition(CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
		godCam->updateCamera();
	};
}

cameraManager::~cameraManager()
{
	//DebugMsg::out("\nDeleting Camera Manager\n");
	delete godCam;
}