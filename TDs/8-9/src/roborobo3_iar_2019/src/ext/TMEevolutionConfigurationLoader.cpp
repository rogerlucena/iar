#if defined PRJ_TMEEVOLUTION || !defined MODULAR

#include "Config/TMEevolutionConfigurationLoader.h"
#include "TMEevolution/include/TMEevolutionWorldObserver.h"
#include "TMEevolution/include/TMEevolutionAgentObserver.h"
#include "TMEevolution/include/TMEevolutionController.h"
#include "WorldModels/RobotWorldModel.h"


TMEevolutionConfigurationLoader::TMEevolutionConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
}

TMEevolutionConfigurationLoader::~TMEevolutionConfigurationLoader()
{
	//nothing to do
}

WorldObserver* TMEevolutionConfigurationLoader::make_WorldObserver(World* wm)
{
	return new TMEevolutionWorldObserver(wm);
}

RobotWorldModel* TMEevolutionConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* TMEevolutionConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new TMEevolutionAgentObserver(wm);
}

Controller* TMEevolutionConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new TMEevolutionController(wm);
}


#endif
