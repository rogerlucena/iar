/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#ifndef TMEBRAITENBERGWORLDOBSERVER_H
#define TMEBRAITENBERGWORLDOBSERVER_H

#include "Observers/WorldObserver.h"

class World;

class TMEbraitenbergWorldObserver : public WorldObserver
{
	protected:
		
	public:
		TMEbraitenbergWorldObserver( World *__world );
		~TMEbraitenbergWorldObserver();
				
		void initPre();
        void initPost();

        void stepPre();
        void stepPost();
		
};

#endif

