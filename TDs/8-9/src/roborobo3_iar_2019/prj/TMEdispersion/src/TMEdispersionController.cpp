/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 * 2018-10-18
 */


#include "TMEdispersion/include/TMEdispersionController.h"
#include "WorldModels/RobotWorldModel.h"
#include "RoboroboMain/roborobo.h"
#include "World/World.h"

// Load readable sensor names
#define NB_SENSORS 12 // should be coherent with gRobotSpecsImageFilename value read from the property file.
#include "Utilities/Sensorbelt.h"

TMEdispersionController::TMEdispersionController( RobotWorldModel *__wm ) : Controller ( __wm )
{
    if ( _wm->_cameraSensorsNb != NB_SENSORS )
    {
        std::cerr << "[CRITICAL] This project assumes robot specifications with " << NB_SENSORS << " sensors (provided: " << _wm->_cameraSensorsNb << " sensors). STOP.\n";
        exit(-1);
    }
}

TMEdispersionController::~TMEdispersionController()
{
    // nothing to do.
}

void TMEdispersionController::reset()
{
    // nothing to do.
}

void TMEdispersionController::step()
{
    // ... a completer ...
}
