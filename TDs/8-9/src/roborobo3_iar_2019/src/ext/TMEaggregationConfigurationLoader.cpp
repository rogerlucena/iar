#if defined PRJ_TMEAGGREGATION || !defined MODULAR

#include "Config/TMEaggregationConfigurationLoader.h"
#include "TMEaggregation/include/TMEaggregationWorldObserver.h"
#include "TMEaggregation/include/TMEaggregationAgentObserver.h"
#include "TMEaggregation/include/TMEaggregationController.h"
#include "WorldModels/RobotWorldModel.h"


TMEaggregationConfigurationLoader::TMEaggregationConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
}

TMEaggregationConfigurationLoader::~TMEaggregationConfigurationLoader()
{
	//nothing to do
}

WorldObserver* TMEaggregationConfigurationLoader::make_WorldObserver(World* wm)
{
	return new TMEaggregationWorldObserver(wm);
}

RobotWorldModel* TMEaggregationConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* TMEaggregationConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new TMEaggregationAgentObserver(wm);
}

Controller* TMEaggregationConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new TMEaggregationController(wm);
}


#endif
