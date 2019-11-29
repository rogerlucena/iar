/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */



#ifndef TMEEVOLUTIONCONTROLLER_H
#define TMEEVOLUTIONCONTROLLER_H

#include "Controllers/Controller.h"
#include "RoboroboMain/common.h"

class RobotWorldModel;

class TMEevolutionController : public Controller
{
	public:
		TMEevolutionController( RobotWorldModel *__wm );
		~TMEevolutionController();
    
		void reset();
		void step();
};


#endif

