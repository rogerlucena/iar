/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#ifndef TMEAGGREGATIONWORLDOBSERVER_H
#define TMEAGGREGATIONWORLDOBSERVER_H

#include "Observers/WorldObserver.h"

class World;

class TMEaggregationWorldObserver : public WorldObserver
{
	protected:
		
	public:
		TMEaggregationWorldObserver( World *__world );
		~TMEaggregationWorldObserver();
				
		void initPre();
        void initPost();

        void stepPre();
        void stepPost();
		
};

#endif

