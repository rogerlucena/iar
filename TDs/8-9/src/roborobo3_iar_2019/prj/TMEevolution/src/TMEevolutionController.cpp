/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 * 2018-10-18
 */


#include "TMEevolution/include/TMEevolutionController.h"
#include "WorldModels/RobotWorldModel.h"
#include "RoboroboMain/roborobo.h"
#include "World/World.h"

// Load readable sensor names
#define NB_SENSORS 12 // should be coherent with gRobotSpecsImageFilename value read from the property file.
#include "Utilities/Sensorbelt.h"

TMEevolutionController::TMEevolutionController( RobotWorldModel *__wm ) : Controller ( __wm )
{
    if ( _wm->_cameraSensorsNb != NB_SENSORS )
    {
        std::cerr << "[CRITICAL] This project assumes robot specifications with " << NB_SENSORS << " sensors (provided: " << _wm->_cameraSensorsNb << " sensors). STOP.\n";
        exit(-1);
    }
}

TMEevolutionController::~TMEevolutionController()
{
    // nothing to do.
}

void TMEevolutionController::reset()
{
    // nothing to do.
}

void TMEevolutionController::step()
{
    // ... a completer ...
}
