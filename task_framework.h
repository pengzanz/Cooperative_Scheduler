#ifndef _TASK_FRAMEWORK_H_
#define _TASK_FRAMEWORK_H_
#include "stdint.h"

typedef struct sTask
{
	void (*pTask)(void);
	uint32 delay;
	uint32 period;
	uint8 runMe;
}sTask;

void Task_Framework_Dispatch_Tasks(void);
uint8 Task_Framework_Add_Task(void (*pTask_)(void), uint32 delay_, uint32 period_);
uint8 Task_Framework_Delete_Task(uint8 taskId_);
void Task_Framework_Update(void);

void Task_Framework_Init(void);
#endif


