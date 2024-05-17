
#include "task.h"
static pTaskFunction pTask[20];

TASK_COMPONENTS Task_Comps[] =
{
		// 状态  计数  周期  函数
		//{0, 1000, 1000, task_test}, /* task 1 Period： 10ms */
		//{0,5,5,led_scan},

		/* Add new task here */
};

uint8_t Tasks_Max = sizeof(Task_Comps) / sizeof(Task_Comps[0]);
// uint8_t Tasks_Max = sizeof(pTask) / sizeof(pTask[0]);

//========================================================================
// 函数: Task_Handler_Callback
// 描述: 任务标记回调函数.
// 参数: None.
// 返回: None.
// 版本: V1.0, 2012-10-22
//========================================================================
void Task_Marks_Handler_Callback(void)
{
	uint8_t i;
	for (i = 0; i < Tasks_Max; i++)
	{
		if (Task_Comps[i].TIMCount) /* If the time is not 0 */
		{
			Task_Comps[i].TIMCount--;		 /* Time counter decrement */
			if (Task_Comps[i].TIMCount == 0) /* If time arrives */
			{
				/*Resume the timer value and try again */
				Task_Comps[i].TIMCount = Task_Comps[i].TRITime;
				Task_Comps[i].Run = 1; /* The task can be run */
			}
		}
	}
}

//========================================================================
// 函数: Task_Pro_Handler_Callback
// 描述: 任务处理回调函数.
// 参数: None.
// 返回: None.
// 版本: V1.0, 2012-10-22
//========================================================================

void Task_Pro_Handler_Callback(void)
{
	uint8_t i;
	for (i = 0; i < Tasks_Max; i++)
	{
		if (Task_Comps[i].Run) /* If task can be run */
		{
			Task_Comps[i].Run = 0; /* Flag clear 0 */
			(*pTask[Task_Comps[i].Task_SN])();
			// Task_Comps[i].TaskHook(); /* Run task */
		}
	}
}
