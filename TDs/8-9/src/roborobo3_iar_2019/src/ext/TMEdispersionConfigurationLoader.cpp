#if defined PRJ_TMEDISPERSION || !defined MODULAR

#include "Config/TMEdispersionConfigurationLoader.h"
#include "TMEdispersion/include/TMEdispersionWorldObserver.h"
#include "TMEdispersion/include/TMEdispersionAgentObserver.h"
#include "TMEdispersion/include/TMEdispersionController.h"
#include "WorldModels/RobotWorldModel.h"


TMEdispersionConfigurationLoader::TMEdispersionConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
}

TMEdispersionConfigurationLoader::~TMEdispersionConfigurationLoader()
{
	//nothing to do
}

WorldObserver* TMEdispersionConfigurationLoader::make_WorldObserver(World* wm)
{
	return new TMEdispersionWorldObserver(wm);
}

RobotWorldModel* TMEdispersionConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* TMEdispersionConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new TMEdispersionAgentObserver(wm);
}

Controller* TMEdispersionConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new TMEdispersionController(wm);
}


#endif
