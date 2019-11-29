#if defined PRJ_TMEBOIDS || !defined MODULAR

#include "Config/TMEboidsConfigurationLoader.h"
#include "TMEboids/include/TMEboidsWorldObserver.h"
#include "TMEboids/include/TMEboidsAgentObserver.h"
#include "TMEboids/include/TMEboidsController.h"
#include "WorldModels/RobotWorldModel.h"


TMEboidsConfigurationLoader::TMEboidsConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
}

TMEboidsConfigurationLoader::~TMEboidsConfigurationLoader()
{
	//nothing to do
}

WorldObserver* TMEboidsConfigurationLoader::make_WorldObserver(World* wm)
{
	return new TMEboidsWorldObserver(wm);
}

RobotWorldModel* TMEboidsConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* TMEboidsConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new TMEboidsAgentObserver(wm);
}

Controller* TMEboidsConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new TMEboidsController(wm);
}


#endif
