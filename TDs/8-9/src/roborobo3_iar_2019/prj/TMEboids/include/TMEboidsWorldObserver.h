/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#ifndef TMEBOIDSWORLDOBSERVER_H
#define TMEBOIDSWORLDOBSERVER_H

#include "Observers/WorldObserver.h"

class World;

class TMEboidsWorldObserver : public WorldObserver
{
	protected:
		
	public:
		TMEboidsWorldObserver( World *__world );
		~TMEboidsWorldObserver();
				
		void initPre();
        void initPost();

        void stepPre();
        void stepPost();
		
};

#endif

