#include "zero.h"

sPtcCtrl_t stPtc;

/**
 * @brief 控制块的初始化
 * 
 * @details 
 */
void zero_init(void)
{
    stPtc.GridZero1 = 0;
    stPtc.GridZero0 = 0;
    stPtc.GridZeroCnt = 0;
    stPtc.GridZeroTh = sizeof(stPtc.HeatWave) * 8; // 输出分辨率16位
    stPtc.GridTrigOnTh = 5000 / TIME_FUN_CALL_US;  // stPtc.GridTrigOnTh * TIME_FUN_CALL_US  = 5ms 半波周期 这里驱动时长为半个周期
    stPtc.HeatWave = 0xF0F0;   //
    stPtc.contorlStage[A] = STAGE_OUTPUT_DIS;
    stPtc.contorlStage[B] = STAGE_OUTPUT_DIS;
    stPtc.Delay[A] = 0;
    stPtc.Delay[B] = 0;
    stPtc.GridTrigEnCnt[A] = 0;
    stPtc.GridTrigEnCnt[B] = 0;
}

/**
 * @brief 过零补偿控制,补偿分辨率取决于该函数的调用频率,调用频率越高,补偿精度越高
 * @param [in] s 控制块
 *
 * @details
 */
void zero_contorl(sPtcCtrl_t *s)
{
    s->GridZero1 = ZERO_VAL;  //本次检测IO电平值
    char type = A;

    /* ---------------------------------- 过零判断 ---------------------------------- */
    if ((s->GridZero0 == LOW && s->GridZero1 == HIGH)) // A类型过零 
    {
        s->GridZeroCnt++;
        if (s->GridZeroCnt > (s->GridZeroTh - 1))
            s->GridZeroCnt = 0;

        if ((s->HeatWave << s->GridZeroCnt) & 0x8000)
        {
#if COMPENSATE
            s->contorlStage[A] = STAGE_COMPENSATE;
            s->Delay[A] = 0;
#else
            s->GridTrigEnCnt[A] = 0;
            s->contorlStage[A] = STAGE_OUTPUT_EN;

#endif
        }

    }

    if ((s->GridZero0 == HIGH && s->GridZero1 == LOW)) // B类型过零 
    {
        s->GridZeroCnt++;
        if (s->GridZeroCnt > (s->GridZeroTh - 1))
            s->GridZeroCnt = 0;

        if ((s->HeatWave << s->GridZeroCnt) & 0x8000)
        {
#if COMPENSATE
            s->contorlStage[B] = STAGE_COMPENSATE;
            s->Delay[B] = 0;
#else
            s->GridTrigEnCnt[B] = 0;
            s->contorlStage[B] = STAGE_OUTPUT_EN;

#endif
        }

    }

    for (type = A; type <= B; type++)
    {

        switch (s->contorlStage[type])
        {
        case STAGE_OUTPUT_DIS:
            s->Out[type] = 0;
            break;
        case STAGE_COMPENSATE:

            s->Delay[type]++;

            if (s->Delay[type] > (type == A ? (PERIOD_HALF_WAVE + CAL_A) : (PERIOD_HALF_WAVE + CAL_B)))
            {
                s->Delay[type] = 0;
                s->GridTrigEnCnt[type] = 0;
                s->contorlStage[type] = STAGE_OUTPUT_EN;
            }

            break;
        case STAGE_OUTPUT_EN:
            s->Out[type] = 1;
            s->GridTrigEnCnt[type]++;

            if (s->GridTrigEnCnt[type] > s->GridTrigOnTh)
            {
                s->contorlStage[type] = STAGE_OUTPUT_DIS;
            }
            break;

        default:

            break;
        }
    }
        s->GridZero0 = s->GridZero1; // 记录这次的电平值，用于下次过零判断
        if(s->Out[A] || s->Out[B])
        {
            PTC_CTR_ONN;
        }
        else
        {
            PTC_CTR_OFF;
        }
}


