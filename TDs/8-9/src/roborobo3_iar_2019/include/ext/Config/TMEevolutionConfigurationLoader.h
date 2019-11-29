/*
 * TMEevolutionConfigurationLoader.h
 */

#ifndef TMEEVOLUTIONCONFIGURATIONLOADER_H
#define	TMEEVOLUTIONCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class TMEevolutionConfigurationLoader : public ConfigurationLoader
{
	public:
		TMEevolutionConfigurationLoader();
		~TMEevolutionConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};

#endif
