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
    stPtc.HeatWave = 0;
    stPtc.stage[A] = STAGE_OUTPUT_DIS;
    stPtc.stage[B] = STAGE_OUTPUT_DIS;
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

    /* ---------------------------------- 过零判断 ---------------------------------- */
    if ((s->GridZero0 == LOW && s->GridZero1 == HIGH)) // A类型过零 
    {
        s->GridZeroCnt++;
        if (s->GridZeroCnt > (s->GridZeroTh - 1))
            s->GridZeroCnt = 0;

        if ((s->HeatWave << s->GridZeroCnt) & 0x8000)
        {
            s->stage[A] = STAGE_COMPENSATE;
        }
    }

    if ((s->GridZero0 == HIGH && s->GridZero1 == LOW)) // B类型过零 
    {
        s->GridZeroCnt++;
        if (s->GridZeroCnt > (s->GridZeroTh - 1))
            s->GridZeroCnt = 0;

        if ((s->HeatWave << s->GridZeroCnt) & 0x8000)
        {
            s->stage[B] = STAGE_COMPENSATE;
        }
    }

    for (char i = A; i <= B; i++)
    {
        switch (s->stage[i])
        {
        case STAGE_OUTPUT_DIS:
            PTC_CTR_OFF;
            break;
        case STAGE_COMPENSATE:
#if COMPENSATE
            s->Delay[i]++;
            if (s->Delay[i] > (i == A ? (PERIOD_HALF_WAVE + CAL_A):(PERIOD_HALF_WAVE + CAL_B))) 
            {
                s->Delay[i] = 0;
                s->GridTrigEnCnt[i] = 0;
                s->stage[i] = STAGE_OUTPUT_EN;
            }
#else
            s->stage[i] = STAGE_OUTPUT_EN;
#endif
            break;
        case STAGE_OUTPUT_EN:
            PTC_CTR_ONN;
            s->GridTrigEnCnt[i]++;
            if (s->GridTrigEnCnt[i] > s->GridTrigOnTh)
            {
                s->stage[i] = STAGE_OUTPUT_DIS;
            }
            break;

        default:
            break;
        }
    }
    s->GridZero0 = s->GridZero1;  //记录这次的电平值，用于下次过零判断
}

/**
 * @brief 此为控制发热的参考函数
 *
 * @details
 */
void heat_test(void)
{
    stPtc.HeatWave = 0x5555; // 0101 0101 0101 0101 波形将会和这16bit一样 1：输出 0：不输出
}