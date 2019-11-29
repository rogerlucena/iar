/*
 * TMEboidsConfigurationLoader.h
 */

#ifndef TMEBOIDSCONFIGURATIONLOADER_H
#define	TMEBOIDSCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class TMEboidsConfigurationLoader : public ConfigurationLoader
{
	public:
		TMEboidsConfigurationLoader();
		~TMEboidsConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};

#endif
