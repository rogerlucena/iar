/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
 
#ifndef TMEDISPERSIONAGENTOBSERVER_H
#define TMEDISPERSIONAGENTOBSERVER_H 

#include "Observers/AgentObserver.h"

class RobotWorldModel;

class TMEdispersionAgentObserver : public AgentObserver
{
	public:
		TMEdispersionAgentObserver( );
		TMEdispersionAgentObserver( RobotWorldModel *__wm );
		~TMEdispersionAgentObserver();
				
		void reset() override;
		void stepPre() override;
		
};


#endif

