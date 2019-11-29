/*
 * TMEbraitenbergConfigurationLoader.h
 */

#ifndef TMEBRAITENBERGCONFIGURATIONLOADER_H
#define	TMEBRAITENBERGCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class TMEbraitenbergConfigurationLoader : public ConfigurationLoader
{
	public:
		TMEbraitenbergConfigurationLoader();
		~TMEbraitenbergConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};

#endif
