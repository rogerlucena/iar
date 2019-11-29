/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
 
#ifndef TMEAGGREGATIONAGENTOBSERVER_H
#define TMEAGGREGATIONAGENTOBSERVER_H 

#include "Observers/AgentObserver.h"

class RobotWorldModel;

class TMEaggregationAgentObserver : public AgentObserver
{
	public:
		TMEaggregationAgentObserver( );
		TMEaggregationAgentObserver( RobotWorldModel *__wm );
		~TMEaggregationAgentObserver();
				
		void reset() override;
		void stepPre() override;
		
};


#endif

