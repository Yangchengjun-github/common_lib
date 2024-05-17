/**
 * @file bat.c
 * @author Yangchengjun (1483609140@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-10
 * 
 * @copyright Copyright (c) 2024 个人
 * 
 */
#include "bat.h"
bat_t xbat;
void init_bat()
{
    
}

void task_bat(void)
{

    static unsigned long timer_full= 0;
    static unsigned int rep = 0;
    xbat.adc = 0;  //TODO  这里对接实际的电池电压采集

    if(!ISCHARGING()) //放电
    {
        if (xbat.adc > 3400 * 2)
        {
            xbat.percent_current = BAT_PER100;
        }
        else if (xbat.adc > 3350* 2 && xbat.percent_current == BAT_PER100)
        {
            xbat.percent_current = BAT_PER100;
        }
        else if (xbat.adc > 3200 * 2)
        {
            xbat.percent_current = BAT_PER66;
        }
        else if (xbat.adc > 3150 * 2 &&xbat.percent_current == BAT_PER66)
        {
            xbat.percent_current = BAT_PER66;
        }
        else if (xbat.adc > 3050 * 2)
        {
            xbat.percent_current = BAT_PER33;
        }
        else if (xbat.adc > 3000* 2 &&xbat.percent_current == BAT_PER33)
        {
            xbat.percent_current = BAT_PER33;
        }
        else if (xbat.adc > 2950 * 2)
        {
            xbat.percent_current = BAT_PER20;
        }
        else if (xbat.adc > 2900 * 2 && xbat.percent_current == BAT_PER20)
        {
            xbat.percent_current = BAT_PER20;
        }
        else if (xbat.adc > 2800 * 2)
        {
            xbat.percent_current = BAT_PER10;
        }
        else 
        {
            xbat.percent_current = BAT_PER0;
        }
        if(xbat.percent_current < xbat.percent_display)
        {
            rep++;
            if(rep > 1000) // 10s 电量减1
            {
                rep = 0;
                if(xbat.percent_display > BAT_PER0)
                    xbat.percent_display --;
               
            }
            
        }
        else
        {
            rep = 0;
        }
    }
    else  //充电
    {
        if (xbat.adc > 4150 * 2 )//&& ISFULL())
        {
            xbat.percent_current = BAT_PER100;
        }
        else if (xbat.adc > 4100 * 2 && xbat.percent_current == BAT_PER100 )//&& ISFULL())
        {
            xbat.percent_current = BAT_PER100;
        }
        else if (xbat.adc > 4100* 2)
        {
            xbat.percent_current = BAT_PER66;
        }
        else if (xbat.adc > 4050* 2 && xbat.percent_current == BAT_PER66)
        {
            xbat.percent_current = BAT_PER66;
        }
        else if (xbat.adc > 3900 * 2)
        {
            xbat.percent_current = BAT_PER33;
        }
        else if (xbat.adc > 3850 * 2 && xbat.percent_current == BAT_PER33)
        {
            xbat.percent_current = BAT_PER33;
        }
        else 
        {
            xbat.percent_current = BAT_PER10;
        }
        if (xbat.percent_current > xbat.percent_display)
        {
            rep++;
            if (rep > 1000) // 10s 电量减1
            {
                rep = 0;
                if(xbat.percent_display < BAT_PER100)
                    xbat.percent_display ++;              
            }
        }
        else
        {
            rep = 0;  

        }       
        
    }


    /* ----------------------- 充电时电压接近8.4，充电达到一定时间强制充满信号成立 ---------------------- */
    if(ISCHARGING())
    {
        if (xbat.adc > 4180 * 2 )
        {
            timer_full++;

            if (timer_full >= (unsigned long)40 * 60 * 100)
            {
                timer_full = (unsigned long)40 * 60 * 100;
                xbat.percent_display = BAT_PER100;
            }
        }
    }
    else
    {
        timer_full = 0;
    }
}
