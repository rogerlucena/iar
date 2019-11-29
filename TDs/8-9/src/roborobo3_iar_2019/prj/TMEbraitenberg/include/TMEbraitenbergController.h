/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */



#ifndef TMEBRAITENBERGCONTROLLER_H
#define TMEBRAITENBERGCONTROLLER_H

#include "Controllers/Controller.h"
#include "RoboroboMain/common.h"

class RobotWorldModel;

class TMEbraitenbergController : public Controller
{
	public:
		TMEbraitenbergController( RobotWorldModel *__wm );
		~TMEbraitenbergController();
    
		void reset();
		void step();
};


#endif

