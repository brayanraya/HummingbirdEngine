#ifndef _HUMMINGBIRDCORE
#define _HUMMINGBIRDCORE

//Singleton Managers
#include "../Hummingbird Engine/Main Game/hummingbirdEngine.h"
#include "../Hummingbird Engine/Asset Manager/Shader Manger/shaderManager.h"
#include "../Hummingbird Engine/Asset Manager/Model Manger/modelManager.h"
#include "../Hummingbird Engine/Asset Manager/Texture Manager/textureManager.h"
#include "../Hummingbird Engine/Asset Manager/Image Manger/imageManager.h"
#include "../Hummingbird Engine/Scene Manager/Scene/sceneManager.h"
#include "../Hummingbird Engine/Asset Manager/Terrain Manager/terrainManager.h"
#include "../Hummingbird Engine/Asset Manager/Sound Manager/SoundManager.h"
#include "../Hummingbird Engine/Render Manager/Camera Manager/cameraManager.h"
//for Game Objects
#include "../Hummingbird Engine/Scene Manager/Attributes/Drawable/drawable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Updateable/updateable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Collidable/collideable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Alarmable/alarmable.h"


/*! \mainpage HummingBird 0.02 API documentation
*
* \section contents Contents
* General:<br/>
* @ref intro <br/>
* @ref features <br/>
* @ref tipsandtricks <br/>
* @ref concept <br/>
* <br/>
* \section intro Introduction
*
* Welcome to the Hummingbird Engine Documentation. This page should give you a short overview
* over the Hummingbird Engine, a simple Game Engine built around the Azul Core.
*
* The Hummingbird Engine is intended to be an easy-to-use 3d game engine, so
* this documentation is an important part of it. If you have any questions or
* suggestions just send an email to brayanraya@gmail.com.
*
* <br/>
*
* \section features Features Within Hummingbird Engine.
*
* The Hummingbird Engine is a simple 3D
* cross platform game engine written in C++ with IrrKlang and the Azul Core API.
* It has many features availible for novice and expert game designers: including
* Alarms, Collision, and Sound.
* <ul>
*               <li>Tiered Collsion</li>
*               <li>Alarm Callbacks</li>
*               <li>Automated Managers</li>
*               <li>Game Pause and Step Feature</li>
*               <li>Terrain Generation Via Hightmap</li>
*               <li>God Mode Camera</li>
* </ul>
* IrrKlang supplys the sound functionality with the following types
* <ul>
*               <li>RIFF WAVE (*.wav)</li>
*               <li>Ogg Vorbis (*.ogg)</li>
*               <li>MPEG-1 Audio Layer 3 (*.mp3)</li>
*               <li>Free Lossless Audio Codec (*.flac)</li>
*               <li>Amiga Modules (*.mod)</li>
*               <li>Impulse Tracker (*.it)</li>
*               <li>Scream Tracker 3 (*.s3d)</li>
*               <li>Fast Tracker 2 (*.xm)</li>
* </ul>
* Azul supplys the texture functionality with the following types
* <ul>
*               <li>TARGA (*.tga)</li>
*               <li>PNG (*.png)</li>
* </ul>
* Azul supplys the Model functionality with the following types
* <ul>
*               <li>AZUL (*.azul)</li>
* </ul>
* <br/>
* <br/>
* <br/>
* \section tipsandtricks Tips and Tricks
*
* This section lists a few tips you might consider when messing around with Hummingbird:
*
* <ul>
*               <li> Alarms(as well as many other types) will triggers an Exception if you attempt to 
*					 assign the same alarm more than once.</li>
*                  
*               <li> Remember that you are able to create factories for game objects to make things simpler. </li>
*
*               <li> There is a userSettings.cpp that can be used for 1 time user defined settings like window size
*                    and clear color.</li>
*
* </ul>
*
* <br/>
*
* \section concept Starting up the Engine
*
* The Hummingbird Engine is designed so that it is very easy to create everything, its interface should
* be very simple to use. The very first order of buisness is to modify the userSettings.cpp
*
* \code
* // ...
*	setWindowName("Hummingbird Engine"); 
*	setWidthHeight(1147, 631); // 
*	SetClearColor(0.000000000f, 0.749019623f, 1.000000000f, 1.000000000f); //DeepSkyBlue
* // ...
* \endcode
*
* The Hummingbird Engine will next need access to all the models, textures, sounds, etc.
* This information is located in the userResources.cpp and the respective folders are in the
* root directory under the Assets Folder.
* Remember the First string is the name you will need later to create Game Objets later.
* \code
* // ...
*	//---------------------------------------------------------------------------------------------------------
*	// Load the Models
*	//---------------------------------------------------------------------------------------------------------
*	modelManager::loadModel("pModelT99B", "t99body.azul");				//MultiMesh Azul Model
*	modelManager::loadModel("pModelT99T", "t99turret.azul");			//MultiMesh Azul Model
*	modelManager::loadModel("pToySoldier", "raya_toySoldier.azul");		//MultiTexture Azul Model
*	//---------------------------------------------------------------------------------------------------------
*	// Load the Shaders
*	//---------------------------------------------------------------------------------------------------------
*	shaderManager::loadShader("pShaderObject_texture", "textureFlatRender"); //OpenGL Shader Language
*	//---------------------------------------------------------------------------------------------------------
*	// Load the Textures
*	//---------------------------------------------------------------------------------------------------------
*	textureManager::loadTexture("pSpaceFrigateTex", "space_frigate.tga"); //TGA for Textures only
*	textureManager::loadTexture("pStitch", "stitch.png"); //PNG or TGA for images
*	//---------------------------------------------------------------------------------------------------------
*	// Load the Images
*	//---------------------------------------------------------------------------------------------------------
*	ImageManager::loadImage("pImageGreen", "pAliensTex"); //Uses previous Texture file and uses the whole 
*														  //texture to create and image
*	ImageManager::loadImage("pImage1", "pFontTex", 20,380,30,40);
*	//---------------------------------------------------------------------------------------------------------
*	// Load the Terrain
*	//---------------------------------------------------------------------------------------------------------
*	terrainManager::loadTerrain("pBumpy", "HMTest1.tga", "pTextPlane", 2000);
*	//---------------------------------------------------------------------------------------------------------
*	// Load the Terrain
*	//---------------------------------------------------------------------------------------------------------
*	SoundManager::loadSound("GunShot", "Gunshot.wav");
*	//---------------------------------------------------------------------------------------------------------
*	// Load the Start Scene
*	//---------------------------------------------------------------------------------------------------------
*	sceneManager::setStartScene(new defaultScene);
* // ...
* \endcode
*
* Note the Start Scene has been set to be the defaultSceneClass. This is a scene that has nothing inside of it.
* We can create our own sceneClass by deriving from Scene. Below you will see an example of a User Created Scene.
* \code
* // ...
* #include "HummingBirdCore.h"
* class userScene : public scene
*	{
*	public:
*		userScene();
*		~userScene();
*		virtual void sceneEnd();
*		virtual void initialize();
*	private:
*		gameObjectType* name;
*		std::list<collisionTestCommandBase*>::iterator frigateANDbullet;
*	}
* // ...
* \endcode
*
*	SceneEnd() and Initialize() should remove all objects from the screen. In this case we would call name->SceneExit() 
*	and name->SceneEntry() respectively. Also in the SceneEnd() and Initialize() we declare the terrain and register collision pairs.
* \code
* // ...
*void userScene::initialize()
*	{
*		SetTerrain("pBumpy");
*		SetCollisionTerrain<toySoldier>();
*		guy = new toySoldier();
*		vroom = new tank();
*		tankANDSoldier = registerCollideablePair<tank, toySoldier>();
*	}
* // ...
* \endcode
* 
* Lets now take a look how we create those game objects. The first thing is to derive your gameObject class from Updateable, Drawable, Alarmable, Collidable
* and Inputable for every system type you want. A class with all 5 active will look something like this:
* \code
* // ...
*	class thisObjectClass: public drawable, public updateable, public alarmable, public collideable,public inputable
*	{
*	public:
*		thisObjectClass();									//Default Constuctor
*		~thisObjectClass();									//Destuctor
*
*		void sceneEntry();									//Scene Entry: All GameObjects use this.
*		void sceneExit();									//Scene Exit: All GameObjects use this.
*		virtual void draw() override;						//Renders Object on Screen: All Drawables use this.
*		virtual void drawHUD() override;					//Renders Sprites on Screen after draw() calls: All Drawables use this.
*		virtual void update() override;						//Updates Object: All Updateables use this.
*		virtual void keyPress(AZUL_KEY k) override;			//Callback when KeyPressed: All Inputables use this.
*		virtual void keyRelease(AZUL_KEY k) override;		//Callback when KeyRelease: All Inputables use this.
*		virtual void alarm0()override;						//Called when Alarm0 was set and has currently Triggered: 
*															//All Alarmables use this.
*
*		virtual void alarm1()override;						//Called when Alarm1 was set and has currently Triggered:
*															//All Alarmables use this.
*
*		virtual void alarm2()override;						//Called when Alarm2 was set and has currently Triggered:
*															//All Alarmables use this.
*
*		virtual void alarm3()override;						//Called when Alarm3 was set and has currently Triggered:
*															//All Alarmables use this.
*
*		void collision(OtherObjectClass*);					//Called when A collision between chosen Collision Volume has occured. 
*															//NOTE: The OtherObjectClass must be comparable to the registerCollidiblePair in the current Scene.
*															// AND the OtherObjectClass must have the same call but with (thisObjectClass*) as the variable.
*		void TerrainCollision()override;					//Called when a collision between the object collides with terrain.
*															//Note: This will only be called if SetCollisionTerrain<C1>(); is called in Scene with the current Object as C1;
*	}
* \endcode
* That should cover the basics of how to get an object on to the scene. Thank you for selecting to use the Hummingbird Engine. 
* Additional Infomation is available in the hyperlinks above. Have fun and make your games fun! :D
* <br/>

*/




#endif // !_HUMMINGBIRDCORE
