/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 * 2018-10-18
 */


#include "TMEboids/include/TMEboidsController.h"
#include "WorldModels/RobotWorldModel.h"
#include "RoboroboMain/roborobo.h"
#include "World/World.h"

// Load readable sensor names
#define NB_SENSORS 12 // should be coherent with gRobotSpecsImageFilename value read from the property file.
#include "Utilities/Sensorbelt.h"

TMEboidsController::TMEboidsController( RobotWorldModel *__wm ) : Controller ( __wm )
{
    if ( _wm->_cameraSensorsNb != NB_SENSORS )
    {
        std::cerr << "[CRITICAL] This project assumes robot specifications with " << NB_SENSORS << " sensors (provided: " << _wm->_cameraSensorsNb << " sensors). STOP.\n";
        exit(-1);
    }
}

TMEboidsController::~TMEboidsController()
{
    // nothing to do.
}

void TMEboidsController::reset()
{
    // nothing to do.
}

int TMEboidsController::isRobotAt(int id) {
	if(getRobotIdAt(id) != -1)
		return 1;
	return 0;
}

double TMEboidsController::getmin(int a, int b, int c)
{
	double a_dist = getDistanceAt(a);
	double b_dist = getDistanceAt(b);
	double c_dist = getDistanceAt(c);
	if(isRobotAt(a) && (a_dist < b_dist || !isRobotAt(b)) && (a_dist < c_dist || !isRobotAt(c))){
		return a_dist;
	}
	else if(isRobotAt(b) && (b_dist < a_dist || !isRobotAt(a)) && (b_dist < c_dist || !isRobotAt(c))){
		return b_dist;
	}
	else if(isRobotAt(c) && (c_dist < a_dist || !isRobotAt(a)) && (c_dist < b_dist || !isRobotAt(b))){
		return c_dist;
	}
	return 10000; //no robot seen
}

double TMEboidsController::getMeanDistGauche() {
	double sumdist = 0;
	int nbrobotsvus = 0;
	for ( int i = 0 ; i != NB_SENSORS ; i++ ) // also possible to check each sensor separatly using SENSOR_L, SENSOR_R, etc. (check Utilities/Sensorbelt.h)
    {
        if ( isRobotAt(i) )
        {
            int robotId = getRobotIdAt(i);
            if ( robotId != -1 )
            {
            	if( ( i >= 0 && i <= 4) || i == 11) { // see numbers in sensorbelt.h
	             	sumdist += getDistanceAt(i);
	             	nbrobotsvus += 1;
	            }
            }
        }
    }
    if(nbrobotsvus != 0)		
  		return sumdist/nbrobotsvus;

  	return 0;
}

double TMEboidsController::getMeanDistDroite() {
	double sumdist = 0;
	int nbrobotsvus = 0;
	for ( int i = 0 ; i != NB_SENSORS ; i++ ) // also possible to check each sensor separatly using SENSOR_L, SENSOR_R, etc. (check Utilities/Sensorbelt.h)
    {
        if ( isRobotAt(i) )
        {
            int robotId = getRobotIdAt(i);
            if ( robotId != -1 )
            {
            	if( !( ( i >= 0 && i <= 4) || i == 11)) { // see numbers in sensorbelt.h
	             	sumdist += getDistanceAt(i);
	             	nbrobotsvus += 1;
	            }
            }
        }
    }
    if(nbrobotsvus != 0)		
  		return sumdist/nbrobotsvus;

  	return 0;
}



double TMEboidsController::getMeanOrientation() {
	double sumorientation = 0;
	int nbrobotsvus = 0;
	for ( int i = 0 ; i != NB_SENSORS ; i++ ) // also possible to check each sensor separatly using SENSOR_L, SENSOR_R, etc. (check Utilities/Sensorbelt.h)
    {
        if ( isRobotAt(i) )
        {
            int robotId = getRobotIdAt(i);
            if ( robotId != -1 )
            {
             	sumorientation += getRobotRelativeOrientationAt( i );
             	nbrobotsvus += 1;
            }
        }
    }
    if(nbrobotsvus != 0)		
  		return sumorientation/nbrobotsvus;

  	return 0; //0 = nothing
}

int TMEboidsController::getNbRobotsVus() {
	int nbrobotsvus = 0;
	for ( int i = 0 ; i != NB_SENSORS ; i++ ) // also possible to check each sensor separatly using SENSOR_L, SENSOR_R, etc. (check Utilities/Sensorbelt.h)
    {
        if ( isRobotAt(i) )
        {
            int robotId = getRobotIdAt(i);
            if ( robotId != -1 )
            {
	             nbrobotsvus += 1;
            }
        }
    }
    return nbrobotsvus;
}

int TMEboidsController::getNbRobotsVusAgauche() {
	int nbrobotsvus = 0;
	for ( int i = 0 ; i != NB_SENSORS ; i++ ) // also possible to check each sensor separatly using SENSOR_L, SENSOR_R, etc. (check Utilities/Sensorbelt.h)
    {
        if ( isRobotAt(i) )
        {
            int robotId = getRobotIdAt(i);
            if ( robotId != -1 )
            {
            	if( ( i >= 0 && i <= 4) || i == 11) // see numbers in sensorbelt.h
	             	nbrobotsvus += 1;
            }
        }
    }
    return nbrobotsvus;
}


void TMEboidsController::step()
{
	/*  subsomption
		level 0 - evitement de murs
		level 1 - répulsion
		level 2 - attraction
		level 3 - orientation
		level 4 - aller tout droit avec noise

	*/

	setTranslation( sin( ( ( getDistanceAt(SENSOR_FFL) + getDistanceAt(SENSOR_FFR) ) / 2.0 )* M_PI / 4.0) );
    
    double distanceOnMyLeft = getDistanceAt(SENSOR_L) + getDistanceAt(SENSOR_FL) + getDistanceAt(SENSOR_FFL);
    double distanceOnMyRight = getDistanceAt(SENSOR_R) + getDistanceAt(SENSOR_FR) + getDistanceAt(SENSOR_FFR);
    
    double rotationDelta = 0.3;
    double noiseAmplitude = 0.01;

    double mingauche = getmin(SENSOR_FFL, SENSOR_FL, SENSOR_L);
    double mindroit = getmin(SENSOR_FFR, SENSOR_FR, SENSOR_R);

    double seuilrepulsion = 0.2;
    double seuilattraction = 0.8;

    int iswall = (getWallAt(SENSOR_FFL) || getWallAt(SENSOR_FL) || getWallAt(SENSOR_L) || getWallAt(SENSOR_FFR) || getWallAt(SENSOR_FR) || getWallAt(SENSOR_R));

    /*
		USE: 
		double getMeanDist();
		int getNbRobotsVus();
		int getNbRobotsVusAgauche();
    */
    double dist_masscenter = 0;
    if(getMeanDistGauche() > getMeanDistDroite()) // val abs
    	dist_masscenter = getMeanDistGauche() - getMeanDistDroite();
    else
    	dist_masscenter = getMeanDistDroite() - getMeanDistGauche();

    std::cout << "dist_masscenter = " << dist_masscenter << std::endl;

    int nbrobotsvus = getNbRobotsVus();
    int nbrobotsvus_gauche = getNbRobotsVusAgauche();

    //level 0 - evitement mur braitenberg
    if(iswall) {		
    	if ( gRobotDisplayFocus && getId() == gRobotIndexFocus ) std::cout <<  "IS WALL" << std::endl;
	    //setRotation( +rotationDelta * (distanceOnMyRight - distanceOnMyLeft )); 
	    if ( distanceOnMyLeft < distanceOnMyRight )
	        setRotation( +rotationDelta );
	    else if ( distanceOnMyRight < distanceOnMyLeft )
	        setRotation( -rotationDelta );
	}
	//level 1 - répulsion
	else if(nbrobotsvus > 0 && dist_masscenter <= seuilrepulsion) {
		if ( gRobotDisplayFocus && getId() == gRobotIndexFocus ) std::cout <<  "REPULSION" << std::endl;

		if(nbrobotsvus_gauche > nbrobotsvus/2) // il y en a plus a gauche
		{ 
			setRotation( +rotationDelta ); //tourne à droite
		}
		else {
			setRotation( -rotationDelta ); //tourne à gauche
		}
	}
	// level 2 - attraction
	else if(nbrobotsvus > 0 && dist_masscenter >= seuilattraction) {
		if ( gRobotDisplayFocus && getId() == gRobotIndexFocus ) std::cout <<  "ATTRACTION" << std::endl;

		if(nbrobotsvus_gauche > nbrobotsvus/2) // il y en a plus a gauche
		{ 
			setRotation( -rotationDelta ); //tourne à gauche
		}
		else {
			setRotation( +rotationDelta ); //tourne à droite
		}
	}
	// level 3 - orientation
	else if (nbrobotsvus > 0) {
		if ( gRobotDisplayFocus && getId() == gRobotIndexFocus ) std::cout <<  "ORIENTATION" << std::endl;
		setRotation(getMeanOrientation());
	}
	//level 4 - aller tout droit avec noise
	else {
		if ( gRobotDisplayFocus && getId() == gRobotIndexFocus ) std::cout <<  "GO ON" << std::endl;
		//setRotation(0);
        setRotation( noiseAmplitude * ( 1.0 - (double)(random01()*2.0) ) );
	}
	
}
