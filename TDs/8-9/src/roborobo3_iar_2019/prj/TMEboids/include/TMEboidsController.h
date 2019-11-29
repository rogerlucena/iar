/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */



#ifndef TMEBOIDSCONTROLLER_H
#define TMEBOIDSCONTROLLER_H

#include "Controllers/Controller.h"
#include "RoboroboMain/common.h"

class RobotWorldModel;

class TMEboidsController : public Controller
{
	public:
		TMEboidsController( RobotWorldModel *__wm );
		~TMEboidsController();
    
		void reset();
		void step();
};


#endif

