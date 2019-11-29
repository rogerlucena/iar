/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */



#ifndef TMEAGGREGATIONCONTROLLER_H
#define TMEAGGREGATIONCONTROLLER_H

#include "Controllers/Controller.h"
#include "RoboroboMain/common.h"

class RobotWorldModel;

class TMEaggregationController : public Controller
{
	public:
		TMEaggregationController( RobotWorldModel *__wm );
		~TMEaggregationController();
    
		void reset();
		void step();
};


#endif

