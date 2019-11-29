/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
 
#ifndef TMEBRAITENBERGAGENTOBSERVER_H
#define TMEBRAITENBERGAGENTOBSERVER_H 

#include "Observers/AgentObserver.h"

class RobotWorldModel;

class TMEbraitenbergAgentObserver : public AgentObserver
{
	public:
		TMEbraitenbergAgentObserver( );
		TMEbraitenbergAgentObserver( RobotWorldModel *__wm );
		~TMEbraitenbergAgentObserver();
				
		void reset() override;
		void stepPre() override;
		
};


#endif

