/*
 * TMEdispersionConfigurationLoader.h
 */

#ifndef TMEDISPERSIONCONFIGURATIONLOADER_H
#define	TMEDISPERSIONCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class TMEdispersionConfigurationLoader : public ConfigurationLoader
{
	public:
		TMEdispersionConfigurationLoader();
		~TMEdispersionConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};

#endif
