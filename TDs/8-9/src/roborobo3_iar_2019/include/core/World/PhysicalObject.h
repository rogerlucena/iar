/*
 *  PhysicalObject.h
 *  roborobo
 *
 *  Created by Nicolas on 9/4/2014.
 *
 */

#ifndef PHYSICALOBJECT_H
#define PHYSICALOBJECT_H

#include "RoboroboMain/common.h"
#include "Utilities/Geometry.h"

extern SDL_Surface *gScreen;

class PhysicalObject
{
protected :
    int _id;
    
    int type;
    
    int lastRelocationDate; // number of steps since last relocation

    // coordinates (center of object)
    double _xReal;
    double _yReal;
    
    Uint8 _displayColorRed;
    Uint8 _displayColorGreen;
    Uint8 _displayColorBlue;
    
    int regrowTimeMax; // max iterations before object re-appear - load from properties file.
    int regrowTime; // iterations before object re-appear
    bool registered;  // is it scheduled for regrowing? (ie. hidden)
    bool relocateObject; // relocate object when re-appear
    bool overwrite; // write object even if another object/robot will be overwritten.
    
    bool _visible; // display option (default: true)
    
    void init();  // called by constructor only
    
protected:
    int findRandomLocation( );
    
public :
    
    PhysicalObject( int __id ); // use PhysicalObjectFactory instead!
    ~PhysicalObject() { }

    int getId()
    {
        return _id;
    }
    
    double getXReal() { return _xReal; }
    double getYReal() { return _yReal; }
    
    Sint16 getXCenterPixel() { return (Sint16)_xReal; }
    Sint16 getYCenterPixel() { return (Sint16)_yReal; }

    void setCoordinates( double x, double y )
    {
        _xReal = x;
        _yReal = y;
    }
    
    void setDisplayColor( Uint8 r, Uint8 g, Uint8 b )
    {
        _displayColorRed = r;
        _displayColorGreen = g;
        _displayColorBlue = b;
    }
    
    void setType ( int __type ) { type = __type; }
    
    virtual void step() = 0;
    virtual void stepPhysicalObject() final; // default step method. Suggested: call this method from step(). Do not override.
    
    virtual bool canRegister() = 0; // test if register object is possible (use both shape or footprints)
    
    virtual void registerObject(); // register object in the world (write images) -- object-specific implementation. When implementing, call super class.
    
    virtual void unregisterObject() = 0; // unregister object in the world (write blank pixels)

    virtual void isTouched( int __idAgent ) = 0; // callback, triggered by agent
    virtual void isWalked( int __idAgent ) = 0; // callback, triggered by agent
    virtual void isPushed( int __id, std::tuple<double, double> __speed ) = 0; // callback, triggered by collision w/ agent/object
    
    virtual void show(SDL_Surface *surface = gScreen) = 0;
    virtual void hide() = 0;
    
    bool isVisible() { return _visible; }
    
    bool triggerRegrow();
    
    int getType() { return type; }

    static bool isInstanceOf ( int index );
    
    virtual std::string inspect( std::string prefix = "" );
    
    virtual void relocate();
    virtual bool relocate( int x, int y );
    
    int getTimestepSinceRelocation();
    int getLastRelocationDate() { return lastRelocationDate; }
    
    
};

#endif
