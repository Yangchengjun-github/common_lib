#ifndef _ZERO_H_
#define _ZERO_H_

#include "main.h"
#define COMPENSATE              (1)            //补偿开启控制
#define ZERO_VAL                (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0))            //这里改为过零检测IO的输入值
#define PTC_CTR_ONN             (HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET))            //这里改为PTC控制开语句
#define PTC_CTR_OFF             (HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET))                      // 这里改为PTC控制关语句
#define TIME_FUN_CALL_US        (40)           // 调用一次函数的时间us
#define CAL_A                   (10)           //A类过零补偿  如果A类型过零补偿为正数，那么A类型过零补偿的时间就会提前，反之则延后
#define CAL_B                   (-10)          //B类过零补偿  如果B类型过零补偿为负数，那么B类型过零补偿的时间就会提前，反之则延后


#define LOW   (0)
#define HIGH  (1)


#define PERIOD_HALF_WAVE   (10000L / TIME_FUN_CALL_US) //半波周期值


enum
{
    A = 0,
    B,   
};

typedef enum
{
    STAGE_OUTPUT_DIS, // 输出关
    STAGE_COMPENSATE, // 补偿
    STAGE_OUTPUT_EN,  // 输出开

} stage_t;
typedef signed short int16_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

typedef struct
{
    int16_t  GridZero1;                 //本次过零IO电平
    int16_t  GridZero0;                 //上次过零IO电平
    uint16_t Delay[2];                  //延时器
    stage_t  contorlStage[2];           // 控制状态
    int16_t  GridTrigEnCnt[2];          // 驱动计数器
    uint8_t  Out[2];                    //输出控制
    int16_t  GridZeroCnt;               //过零计数器
    int16_t  GridZeroTh;                //控制周期
    int16_t  GridTrigOnTh;              //驱动时间设定值
    uint16_t HeatWave;                  //发热波形控制（控制分辨率取决于该数据类型的bit数）

} sPtcCtrl_t;

void zero_contorl(sPtcCtrl_t *s);
void zero_init(void);
extern sPtcCtrl_t stPtc;

#endif


