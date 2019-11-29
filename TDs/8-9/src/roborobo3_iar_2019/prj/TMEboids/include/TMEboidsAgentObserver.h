/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
 
#ifndef TMEBOIDSAGENTOBSERVER_H
#define TMEBOIDSAGENTOBSERVER_H 

#include "Observers/AgentObserver.h"

class RobotWorldModel;

class TMEboidsAgentObserver : public AgentObserver
{
	public:
		TMEboidsAgentObserver( );
		TMEboidsAgentObserver( RobotWorldModel *__wm );
		~TMEboidsAgentObserver();
				
		void reset() override;
		void stepPre() override;
		
};


#endif

