/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 * 2018-10-18
 */


#include "TMEaggregation/include/TMEaggregationController.h"
#include "WorldModels/RobotWorldModel.h"
#include "RoboroboMain/roborobo.h"
#include "World/World.h"

// Load readable sensor names
#define NB_SENSORS 12 // should be coherent with gRobotSpecsImageFilename value read from the property file.
#include "Utilities/Sensorbelt.h"

TMEaggregationController::TMEaggregationController( RobotWorldModel *__wm ) : Controller ( __wm )
{
    if ( _wm->_cameraSensorsNb != NB_SENSORS )
    {
        std::cerr << "[CRITICAL] This project assumes robot specifications with " << NB_SENSORS << " sensors (provided: " << _wm->_cameraSensorsNb << " sensors). STOP.\n";
        exit(-1);
    }
}

TMEaggregationController::~TMEaggregationController()
{
    // nothing to do.
}

void TMEaggregationController::reset()
{
    // nothing to do.
}

void TMEaggregationController::step()
{
    // ... a completer ...
    if ( gRobotDisplayFocus && getId() == gRobotIndexFocus ) // Execute __only__ for robot under focus (press "F" to focus on a robot, <tab> and <shift>+<tab> to change robot focus)
    {
        std::cout << "Robot #" << getId() << "\n";
        std::cout << "\torientation: " << getOrientation()*180.0 << "°\n";
        Point2d pos = getPosition();
        std::cout << "\tposition: ( " << pos.x << " , " << pos.y << " )\n";
        std::cout << "\tactual translation: " << getActualTranslation() << " (in [-1,+1] wrt min/max values)\n";
        std::cout << "\tactual rotation: " << getActualRotation() << " (in [-1,+1] wrt min/max values)\n";
        
        std::cout << "\tsensorbelt status:" << "\n";
        for ( int i = 0 ; i != NB_SENSORS ; i++ ) // also possible to check each sensor separatly using SENSOR_L, SENSOR_R, etc. (check Utilities/Sensorbelt.h)
        {
            double dist = getDistanceAt(i);
            // if (dist < 0.1)
            // {
            //     setTranslation(0);
            //     break;
            // }
            std::cout << "\t\t[" << i << "] ";
            if ( getWallAt(i) == 1 )
            {
                std::cout << "[dist=" << dist << "] Wall\n";
            }
            else
            {
                int robotId = getRobotIdAt(i);
                if ( robotId != -1 )
                {
                    std::cout << "[dist=" << dist << "] Robot #" << robotId << "\n\t\t      relative orientation wrt robot "<<getId()<<" : " << getRobotRelativeOrientationAt( i )*180.0 << "°\n";
                    
                    // accessing the target robot's controller
                    // can be useful if additional methods have been implemented (e.g. communication)
                    TMEaggregationController* targetRobotController = dynamic_cast<TMEaggregationController*>(getRobotControllerAt(i));
                    std::cout << "\t\t      [double-check] target robot's id really is #" << targetRobotController->getId() << "\n"; // example of use
                    
                }
                else
                {
                    std::cout << "[dist=" << dist << "] Nothing\n";
                }
            }
        }
    }
    
    // * How to use sensors to drive the robot
    // This is an example that code for wall avoidance
    
    setTranslation( sin( ( ( getDistanceAt(SENSOR_FFL) + getDistanceAt(SENSOR_FFR) ) / 2.0 )* M_PI / 2.0) );
    for ( int i = 0 ; i != NB_SENSORS ; i++ )
    {
        double dist = getDistanceAt(i);
        if (dist < 0.1){
        setTranslation(0);
        break;
        }
    }
    
    double distanceOnMyLeft = getDistanceAt(SENSOR_L) + getDistanceAt(SENSOR_FL) + getDistanceAt(SENSOR_FFL);
    double distanceOnMyRight = getDistanceAt(SENSOR_R) + getDistanceAt(SENSOR_FR) + getDistanceAt(SENSOR_FFR);
    
    double rotationDelta = 0.7;
    double noiseAmplitude = 0.01;
    
    // if ( distanceOnMyLeft < distanceOnMyRight )
    //     setRotation( +rotationDelta );
    // else
    //     if ( distanceOnMyRight < distanceOnMyLeft )
    //         setRotation( -rotationDelta );
    //     else
    //         //setRotation( 0.1 - (double)(random01()*0.2));
    //         setRotation( noiseAmplitude * ( 1.0 - (double)(random01()*2.0) ) );
}

