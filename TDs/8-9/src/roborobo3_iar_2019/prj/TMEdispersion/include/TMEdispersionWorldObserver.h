/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#ifndef TMEDISPERSIONWORLDOBSERVER_H
#define TMEDISPERSIONWORLDOBSERVER_H

#include "Observers/WorldObserver.h"

class World;

class TMEdispersionWorldObserver : public WorldObserver
{
	protected:
		
	public:
		TMEdispersionWorldObserver( World *__world );
		~TMEdispersionWorldObserver();
				
		void initPre();
        void initPost();

        void stepPre();
        void stepPost();
		
};

#endif

