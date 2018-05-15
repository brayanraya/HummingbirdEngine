#ifndef _freezeTime
#define _freezeTime

#include "AzulCore.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Hacky system to pause frames and single frame step. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class freezeTime
{
public:
	//------------------------------------
	//Big 4
	//------------------------------------
	freezeTime();
	~freezeTime();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Checks to see if the game is paused.	</summary>
	/// 
	/// <remarks>	Brayan Raya, 2/27/2017. </remarks>
	///
	/// <param name="inTime">	System Time Retrieved From AzulCore. </param>
	///
	/// <returns>	The time in seconds. </returns>
	///-------------------------------------------------------------------------------------------------
	float getTimeInSeconds(float inTime);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Helper function to either pause, resume, or single frame advance. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <param name="inTime">	System Time Retrieved From Azul Core. </param>
	///
	/// <returns>	The current game time before the pause. </returns>
	///-------------------------------------------------------------------------------------------------
	float WaitAndReturnFrozenTime(float inTime);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Checks to see if the key has been released to resume the game. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <param name="inKey">	The current Key. </param>
	///
	/// <returns>	True if it freeze key has been released. </returns>
	///-------------------------------------------------------------------------------------------------
	bool HackedKeyRelease(AZUL_KEY inKey);

private:

	/// <summary>	The total frozen time. </summary>
	float totalFrozenTime = 0;

	/// <summary>	True to freeze mode active. </summary>
	bool freeze_mode_active = false;

	/// <summary>	The freeze key. </summary>
	const AZUL_KEY FREEZE_KEY = AZUL_KEY::KEY_F10;

	/// <summary>	The single frame key. </summary>
	const AZUL_KEY SINGLE_FRAME_KEY = AZUL_KEY::KEY_F11;
};

#endif // _freezeTime