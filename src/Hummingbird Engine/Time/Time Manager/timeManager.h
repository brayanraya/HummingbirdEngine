#ifndef _TimeManager
#define _TimeManager

#include "AzulCore.h"
#include "../Freeze Time/freezeTime.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Used for keeping track of time and time related stats. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class timeManager //Singleton
{
private:
	//------------------------------------
	// Big 4. 
	//------------------------------------
	timeManager() = default;
	~timeManager();
	timeManager(const timeManager&) = delete;
	timeManager& operator=(const timeManager&) = delete;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the instance of Time Manager. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <returns>	The current timeManager. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static timeManager& Instance()
	{
		if (!currentInstanceTimeManager)
			currentInstanceTimeManager = new timeManager;
		return *currentInstanceTimeManager;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Private Function: processes time elapsed. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <param name="inTime">	The current system time. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void privProcessTime(float inTime);

	/// <summary>	Singleton Instance Pointer. </summary>
	static timeManager* currentInstanceTimeManager;

	/// <summary>	The previous time. </summary>
	float previousTime = 0;

	/// <summary>	The current time. </summary>
	float currentTime = 0;

	/// <summary>	The frame number. </summary>
	float frameNumber = 0;

	/// <summary>	The second time holder. </summary>
	float secondTimeHolder = 0;
	
	/// <summary>	The current FPS. </summary>
	int currentFPS = 0;
	
	/// <summary>	The average FPS. </summary>
	int averageFPS = 0;
	
	/// <summary>	The pause. </summary>
	freezeTime pause;
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Checks to see if game is paused. If so, game loops in pause state. If not, processes all time
	/// in reference to system time. Caluclates Average and Current Frame. Determines when a second
	/// has passed in system time.
	/// </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <param name="inTime">	The current AZULCORE time. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static void processTime(float inTime) { return Instance().privProcessTime(inTime); }

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets current time. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <returns>	The current time. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static float getCurrentTime() { return Instance().currentTime; }

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets frame number. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <returns>	The frame number. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static float getFrameNumber() { return Instance().frameNumber;}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the FPS. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <returns>	The FPS. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static int getFPS() { return Instance().averageFPS; }
};
#endif // _TimeManager