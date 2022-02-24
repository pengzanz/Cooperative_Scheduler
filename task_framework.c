#include "task_framework.h"

#define SCH_MAX_TASKS    10
sTask schTaskGroup[SCH_MAX_TASKS];

/*********************************************************
*********************************************************/
void Task_Framework_Dispatch_Tasks(void)
{
	uint8 index = 0;
	
	for(index = 0; index < SCH_MAX_TASKS; index++)
	{
		if(schTaskGroup[index].runMe > 0)
		{
			(*(schTaskGroup[index].pTask))();
			schTaskGroup[index].runMe -= 1;
			
			if(schTaskGroup[index].period == 0)
			{
				Task_Framework_Delete_Task(index);
			}
		}
	}
}

/*********************************************************
*********************************************************/
uint8 Task_Framework_Add_Task(void (*pTask_)(void), uint32 delay_, uint32 period_)
{
	uint8 index = 0;
	
	while((schTaskGroup[index].pTask != 0) && index < SCH_MAX_TASKS)
	{
		index++;
	}
	
	if(index == SCH_MAX_TASKS)
	{
		return SCH_MAX_TASKS;
	}
	
	schTaskGroup[index].pTask = pTask_;
	schTaskGroup[index].delay = delay_;
	schTaskGroup[index].period = period_;
	schTaskGroup[index].runMe = 0;
	
	return index;
}

/*********************************************************
*********************************************************/
uint8 Task_Framework_Delete_Task(uint8 taskId_)
{
	uint8 errorCode = 0;
	if(taskId_ < SCH_MAX_TASKS)
	{
		schTaskGroup[taskId_].pTask = 0;
		schTaskGroup[taskId_].delay = 0;
		schTaskGroup[taskId_].period = 0;
		schTaskGroup[taskId_].runMe = 0;
	}
	
	return errorCode;
}

/*********************************************************
*********************************************************/
void Task_Framework_Update(void)
{
	uint8 index = 0;
	
	for(index = 0; index < SCH_MAX_TASKS; index++)
	{
		if(schTaskGroup[index].pTask)
		{
			if(schTaskGroup[index].delay == 0)
			{
				schTaskGroup[index].runMe += 1;
				
				if(schTaskGroup[index].period)
				{
					schTaskGroup[index].delay = schTaskGroup[index].period - 1;
				}
			}
			else
			{
				schTaskGroup[index].delay -= 1;
			}
		}
	}
}

/*********************************************************
*********************************************************/
void Task_Framework_Init(void)
{
	uint8 i = 0;
	
	for(i = 0; i < SCH_MAX_TASKS; i++)
	{
		schTaskGroup[i].pTask = 0;
		schTaskGroup[i].delay = 0;
		schTaskGroup[i].period = 0;
		schTaskGroup[i].runMe = 0;
	}
}

