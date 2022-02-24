
#include "system_framework.h"


int main( void )
{
	System_Framework_Init();
    Task_Framework_Add_Task(App_Test, 0, 100);
    Task_Framework_Add_Task(App_Polling, 0, 200);
	
	while(1)
	{
		Task_Framework_Dispatch_Tasks();
	}
}

//TIMER ISR
void timer_interrupt(void)
{
    Task_Framework_Update();
}
