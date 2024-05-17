
#ifndef _TASK_H_
#define _TASK_H_


#include "main.h"

typedef void (*pTaskFunction)(void);
typedef struct
{
	uint8_t  Run;                        // 任务状态：Run/Stop
	uint16_t TIMCount;                   // 定时计数
	uint16_t TRITime;                    // 重载计数
	uint8_t  Task_SN;
	//void     (*TaskHook)(void);          // 任务函数
} TASK_COMPONENTS;

typedef void (*pTaskFunction)(void);

void Task_Marks_Handler_Callback(void);
void Task_Pro_Handler_Callback(void);
void task_test(void);
void task_init(void);
#endif

