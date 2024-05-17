#ifndef _BAT_H
#define _BAT_H
#include "main.h"

void task_bat(void);

typedef struct 
{
    uint16_t adc;
    enum
    {
        BAT_PER0,
        BAT_PER10,
        BAT_PER20,
        BAT_PER33,
        BAT_PER66,
        BAT_PER100,
    }percent_current,percent_display;

}bat_t;




#endif