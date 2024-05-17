#include "led.h"

xled_t xled;

unsigned int time_blink = 0;

void led_init(void)
{
   //TODO 这里完成LED IO口的初始化
}


void task_led(void)
{
    static unsigned int timer = 0;
    static unsigned int  timer_blink  = 0;
/* -------------------------------------------------------------------------- */
//对消息做出反应，切换程序状态
/* -------------------------------------------------------------------------- */
    if (xled.message.mes1 == 1)
    {
        xled.message.mes1 = 0;       
        xled.status = led_status1;
        timer = 0;
    }
    if (xled.message.mes2 == 1)
    {
        xled.message.mes2 = 0;
        xled.status = led_status2;
        timer = 0;
    }
    if (xled.message.mes3 == 1)
    {
        xled.message.mes3 = 0;
        xled.status = led_status3;
        timer = 0;
    }
    if (xled.message.mes4 == 1)
    {
        xled.message.mes4 = 0;
        xled.status = led_status4;
        timer = 0;
    }
/* -------------------------------------------------------------------------- */
//根据状态执行相应的操作
/* -------------------------------------------------------------------------- */
    switch (xled.status)
    {
    case led_status1:

    case led_status2:
        timer++;
        if (timer == 1)
        {

        }
        else if (timer == 15)
        {

        }  
        else if (timer == 30)
        {

        }
        else if (timer == 45)
        {

        }
        else if (timer == 60)
        {

        }
        else if (timer == 75)
        {

            timer = 0;
            xled.status = led_status1;
        }

        break;
    case led_status3: 
        timer_blink++;
/* -------------------------------------------------------------------------- */
 //code
/* -------------------------------------------------------------------------- */
        break;
    default:
        break;
    }
}


