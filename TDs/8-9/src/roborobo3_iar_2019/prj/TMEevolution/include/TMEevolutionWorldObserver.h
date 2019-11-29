/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#ifndef TMEEVOLUTIONWORLDOBSERVER_H
#define TMEEVOLUTIONWORLDOBSERVER_H

#include "Observers/WorldObserver.h"

class World;

class TMEevolutionWorldObserver : public WorldObserver
{
	protected:
		
	public:
		TMEevolutionWorldObserver( World *__world );
		~TMEevolutionWorldObserver();
				
		void initPre();
        void initPost();

        void stepPre();
        void stepPost();
		
};

#endif

