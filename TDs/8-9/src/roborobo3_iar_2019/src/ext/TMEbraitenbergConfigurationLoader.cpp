#if defined PRJ_TMEBRAITENBERG || !defined MODULAR

#include "Config/TMEbraitenbergConfigurationLoader.h"
#include "TMEbraitenberg/include/TMEbraitenbergWorldObserver.h"
#include "TMEbraitenberg/include/TMEbraitenbergAgentObserver.h"
#include "TMEbraitenberg/include/TMEbraitenbergController.h"
#include "WorldModels/RobotWorldModel.h"


TMEbraitenbergConfigurationLoader::TMEbraitenbergConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
}

TMEbraitenbergConfigurationLoader::~TMEbraitenbergConfigurationLoader()
{
	//nothing to do
}

WorldObserver* TMEbraitenbergConfigurationLoader::make_WorldObserver(World* wm)
{
	return new TMEbraitenbergWorldObserver(wm);
}

RobotWorldModel* TMEbraitenbergConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* TMEbraitenbergConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new TMEbraitenbergAgentObserver(wm);
}

Controller* TMEbraitenbergConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new TMEbraitenbergController(wm);
}


#endif
