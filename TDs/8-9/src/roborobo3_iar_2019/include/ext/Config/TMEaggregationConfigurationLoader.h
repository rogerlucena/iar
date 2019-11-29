/*
 * TMEaggregationConfigurationLoader.h
 */

#ifndef TMEAGGREGATIONCONFIGURATIONLOADER_H
#define	TMEAGGREGATIONCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class TMEaggregationConfigurationLoader : public ConfigurationLoader
{
	public:
		TMEaggregationConfigurationLoader();
		~TMEaggregationConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};

#endif
