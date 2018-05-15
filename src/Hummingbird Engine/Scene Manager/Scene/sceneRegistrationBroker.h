#ifndef _sceneRegistrationBroker
#define _sceneRegistrationBroker

#include <list>
class commandBase;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	A broker to execute commands throughout the scene in Queue Order. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class sceneRegistrationBroker
{
public:	
	//------------------------------------
	//Big 4
	//------------------------------------
	sceneRegistrationBroker() = default;
	~sceneRegistrationBroker();


	/// <summary>	List of commands. </summary>
	using commandList = std::list<commandBase*>;
	/// <summary>	The command list iterator. For Quick delete. </summary>
	using commandListRef = commandList::iterator;


	///-------------------------------------------------------------------------------------------------
	/// <summary>	
	/// 			Executed at the top of the update call(before everything else). 
	/// </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <param name="add">	Adds a command to the scene broker. </param>
	///-------------------------------------------------------------------------------------------------
	void addCommand(commandBase * add);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Executes the commands in the list and removes them from the list. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void executeCommands();
private:

	/// <summary>	List of commands that will be executed in the appropriate managers. </summary>
	commandList commandManagerList;
};
#endif //!__sceneRegistrationBroker
