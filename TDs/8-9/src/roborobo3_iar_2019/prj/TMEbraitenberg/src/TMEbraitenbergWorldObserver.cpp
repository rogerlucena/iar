/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#include "TMEbraitenberg/include/TMEbraitenbergWorldObserver.h"
#include "World/World.h"
#include "Utilities/Misc.h"
#include "TMEbraitenberg/include/TMEbraitenbergController.h"
#include "RoboroboMain/roborobo.h"


TMEbraitenbergWorldObserver::TMEbraitenbergWorldObserver( World *__world ) : WorldObserver( __world )
{
	_world = __world;
}

TMEbraitenbergWorldObserver::~TMEbraitenbergWorldObserver()
{
	// nothing to do.
}

void TMEbraitenbergWorldObserver::initPre() // called *before* creating and locating robots in the environment
{
    // nothing to do.
}

void TMEbraitenbergWorldObserver::initPost() // called just *after* creating and locating robots in the environment
{
    // nothing to do.
}

void TMEbraitenbergWorldObserver::stepPre() // called just *before* the robots move
{
    // The following code shows an example where every 100 iterations, robots are re-located to their initial positions, and parameters are randomly changed.
    /*
    if ( gWorld->getIterations() % 100 == 0 )
    {
        if ( gVerbose && gDisplayMode == 0 )
            std::cout << "Relocating\n";

        for ( int i = 0 ; i != gWorld->getNbOfRobots() ; i++ )
        {
            Robot *robot = (gWorld->getRobot(i));
            
            (*robot).setCoordReal( ...TODO... , ...TODO...  ); // whereever you want, but check locations are empty before.
        }
    }
    */
}

void TMEbraitenbergWorldObserver::stepPost() // called just *after* the robots move
{
    // nothing to do.
}
