/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */



#ifndef TMEDISPERSIONCONTROLLER_H
#define TMEDISPERSIONCONTROLLER_H

#include "Controllers/Controller.h"
#include "RoboroboMain/common.h"

class RobotWorldModel;

class TMEdispersionController : public Controller
{
	public:
		TMEdispersionController( RobotWorldModel *__wm );
		~TMEdispersionController();
    
		void reset();
		void step();
};


#endif

