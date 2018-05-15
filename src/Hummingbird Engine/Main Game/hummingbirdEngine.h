#ifndef GAME_H
#define GAME_H

#include "AzulCore.h"
#include <string>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	The Hummingbird Engine. </summary>
///
/// <remarks>	Braya, 3/2/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class hummingbirdEngine: public Engine //Singleton
{
private:
	//------------------------------------
	//Big 4
	//------------------------------------
	hummingbirdEngine() = default;
	~hummingbirdEngine();
	hummingbirdEngine(const hummingbirdEngine&) = delete;
	hummingbirdEngine& operator=(const hummingbirdEngine&) = delete;

	//------------------------------------
	//Private Functions
	//------------------------------------

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Instance creator for the singleton. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <returns>	A reference to a hummingbirdEngine. </returns>
	///-------------------------------------------------------------------------------------------------
	static hummingbirdEngine& Instance()
	{
		if (!currentInstanceGame)
			currentInstanceGame = new hummingbirdEngine;
		return *currentInstanceGame;
	};

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Initalization Phase of Engine. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void Initialize();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Loads the default content followed by user provided content. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void LoadContent();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Update Cycle of Engine. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void Update();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Draw Cycle of Engine. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void Draw();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Game Termination and unload Content. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void UnLoadContent();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Loads user resources in userResources_cpp. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void LoadUserResources();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Loads user settings in userResources_cpp. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void LoadUserSettings();

	//------------------------------------
	//private variables
	//------------------------------------
	static hummingbirdEngine* currentInstanceGame;

public:	

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Creates the game. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	static void createGame() { Instance().currentInstanceGame->run(); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets window width. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <returns>	The window width. </returns>
	///-------------------------------------------------------------------------------------------------
	static int getWindowWidth() { return Instance().getWidth(); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets window height. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <returns>	The window height. </returns>
	///-------------------------------------------------------------------------------------------------
	static int getWindowHeight() { return Instance().getHeight(); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets system time. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <returns>	The system time. </returns>
	///-------------------------------------------------------------------------------------------------
	static float getSystemTime() { return Instance().GetTimeInSeconds(); };

	static void setClearColor(float r, float g, float b, float a) { return Instance().SetClearColor(r, g, b, a); };

	static void setClearColor(const Vect& v) { return Instance().SetClearColor(v.X(), v.Y(), v.Z(), v.W()); };

};

#endif