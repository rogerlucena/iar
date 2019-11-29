/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
 
#ifndef TMEEVOLUTIONAGENTOBSERVER_H
#define TMEEVOLUTIONAGENTOBSERVER_H 

#include "Observers/AgentObserver.h"

class RobotWorldModel;

class TMEevolutionAgentObserver : public AgentObserver
{
	public:
		TMEevolutionAgentObserver( );
		TMEevolutionAgentObserver( RobotWorldModel *__wm );
		~TMEevolutionAgentObserver();
				
		void reset() override;
		void stepPre() override;
		
};


#endif

