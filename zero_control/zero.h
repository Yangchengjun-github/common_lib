#ifndef _ZERO_H_
#define _ZERO_H_


#define COMPENSATE              (1)            //补偿开启控制
#define ZERO_VAL                (1)            //这里改为过零检测IO的输入值
#define PTC_CTR_ONN             (1)            //这里改为PTC控制开语句
#define PTC_CTR_OFF             (1)            //这里改为PTC控制关语句
#define TIME_FUN_CALL_US        (40)           // 40us调用一次函数
#define CAL_A                   (10)           //A类过零补偿
#define CAL_B                   (-10)          //B类过零补偿


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
    int16_t  GridZero1;                 //本次IO电平
    int16_t  GridZero0;                 //上次IO电平
    uint16_t Delay[2];                  //延时输出（补偿）
    stage_t  stage[2];                  // 控制状态
    int16_t  GridTrigEnCnt[2];          // 驱动持续时间
    int16_t  GridZeroCnt;               //过零计数
    int16_t  GridZeroTh;                //过零计数周期
    int16_t  GridTrigOnTh;              //每次驱动时间
    uint16_t HeatWave;                  //发热控制波形（控制分辨率取决于该数据类型的bit数）
    
} sPtcCtrl_t;

#endif