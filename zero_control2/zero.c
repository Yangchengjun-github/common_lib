#include "task.h"

char cnt_;
char cnt1_;
struct 
{
    unsigned char preiod;
    unsigned char pulse;
    unsigned char counter;
}output_CB = {10,9,0};
void task_debug(void);
void task_run(void)
{
    /* ---------------------------------- 加热控制 ---------------------------------- */

 
        
    if(sys_clk.period_10ms)
    {
        sys_clk.period_10ms = 0;
#if DEBUG
        task_debug();
#endif
        cnt_++;
        cnt1_++;
        if(cnt1_ >= 10)
        {
            cnt_ = 0;
        }
        else if(cnt1_ >= 30)
        {
            cnt1_ = 0;
        }
        if(cnt_ == 2)
        {
            _pb4 = 1;
        }
        else if(cnt_ == 4)
        {
            cnt_ = 0;
            _pb4 = 0;
            
        }
        // task_key();
        // task_bat(BAT_MODE_NORMAL);
        // task_app();
        // task_heat();
        // task_led();
        //_pb4 = !_pb4;
        }
    
}


#if DEBUG

void task_debug(void)  
{
    static unsigned char a = 0;
    a++;
    if(a>=100)
    {
        a = 0;
        UART_SoftWareSendByte(0xaa);
        UART_SoftWareSendByte(0xbb);
        // UART_SoftWareSendByte(sys_arg.system_status);
         //UART_SoftWareSendByte(sys_arg.ui_led_mode);
        // UART_SoftWareSendByte(sys_arg.heat_level);
        // UART_SoftWareSendByte(sys_arg.system_lock);
        // UART_SoftWareSendByte(key_cb.count_press);
        UART_SoftWareSendByte(sys_arg.adc_result[CH_BAT] >> 8);
        UART_SoftWareSendByte(sys_arg.adc_result[CH_BAT]);
        UART_SoftWareSendByte(sys_arg.adc_result[CH_TEM] >> 8);
        UART_SoftWareSendByte(sys_arg.adc_result[CH_TEM]);
        UART_SoftWareSendByte(sys_arg.ntc_err);
        UART_SoftWareSendByte(_pb0);//加热
        // UART_SoftWareSendByte(ISCHARGING()); //充电
        // UART_SoftWareSendByte(ISFULL());     // 充满
        // UART_SoftWareSendByte(sys_arg.bat_percent);
        //my_printf("nihao\n");
    }
    
        
}
#endif

//  

void __attribute((interrupt(0x14))) timerbase_isr(void)
{
    static  unsigned char t = 0;
    // static unsigned char i = 0;
    // static unsigned char g = 0, s = 0, b = 0;
    // _emi = 0;
    // _tbf = 0;
    // _pb3 = ~_pb3;

    t++;
    if (t >= 30)
    {
        t = 0;
        sys_clk.period_10ms = 1;
        // _tbsel0 = 1; // 8192 分频 8M  约 1K
        // _tbsel1 = 1;
        // _tbe = 1;
    }

//     if (display.temp == TEMP_NONE) // 息屏
//     {
//         ledx_z();
//         return;
//     }
// /* ----------------------------------- 扫灯 ----------------------------------- */
//     ledx_z(); // 每次点灯前，io先设为高阻

//     if (i == 0) // 一轮16个灯刷完，再赋值
//     {
//         g = display.temp % 10;
//         s = display.temp / 10 % 10;
//         b = display.temp / 100;
//         if (display.OFF)
//         {
//             // 显示off
//             b = 0;
//             s = 11;
//             g = 11;

//         }
//     }
    
//     if (i < 7) // 百位
//     {
//         if ((display.temp > 99) && (num_code[b] & (1 << i))) // 检查当前的灯是否用与点亮当前的数字,此位为0不显示。
//             led_map(led_code[i][0], led_code[i][1]);         // 相应io口驱动去点亮
//     }
//     else if (i < 14) // 十位
//     {
//         if ((display.temp > 9) && (num_code[s] & (1 << (i - 7))))
//             led_map(led_code[i][0], led_code[i][1]);
//     }
//     else if (i < 21) // 个位
//     {
//         if (num_code[g] & (1 << (i - 14)))
//             led_map(led_code[i][0], led_code[i][1]);
//     }
//     else
//     {

//         if ((i == 21 && display.point1) || (i == 22 && display.point2) || (i == 23 && display.pane1) || (i == 24 && display.pane1) || (i == 25 && display.bat1) || (i == 26 && display.bat2) || (i == 27 && display.bat3) || (i == 28 && display.lightning))
//         {
//             led_map(led_code[i][0], led_code[i][1]);
//         }
//     }

//     i++;
//     if (i == 29)
//     {

//         i = 0;
//     }
//     /* -------------------------------------------------------------------------- */
   

//     _emi = 1;
}
struct 
{
    unsigned char cnt; //中断计数
    unsigned char cnt1; // 中断计数
    unsigned char integer; // 整数
    unsigned char mantissa; // 尾数
    unsigned char cmd; //可控硅控制命令
    unsigned char zero_in_last; //
    unsigned char zero_in_now; //
}xzero;

void timer1_init()
{
    _t1m0 = 0;  //定时器模式
    _t1m1 = 1;
    _t1s = 0; //定时器源选择
    _t1on = 0; //定时器除能

}
/**
 * @brief 
 * @param [in] integer    76us
 * @param [in] mantissa    76/255us
 * 
 * @details 
 */
void timer1_start(unsigned char integer, unsigned char mantissa,unsigned char trigger_cmd)
{
    xzero.cnt = 0;
    xzero.integer = integer;
    xzero.mantissa = mantissa;
    xzero.cmd = trigger_cmd;
    _t1f = 0;  // 清除中断标志
    _t1on = 1; // 定时器使能
    _t1e = 1;  // 定时器中断使能
}

void timer1_stop(void)
{
    _t1on = 0;
    _t1e = 0;
}

void __attribute((interrupt(0x0C))) timer1_isr(void) // 定时器中断函数
{
    _t1f = 0;
    if(xzero.cmd == 0)
    {
        xzero.cnt1++;
    }
    xzero.cnt++;
    _tmr1 = 0x00;  //整数 计数给定
    if (xzero.cnt == xzero.integer) //
    {
        _tmr1 = xzero.mantissa;  //尾数 给定
    }
    else if (xzero.cnt == xzero.integer + 1 ) //
    {
        if (xzero.cmd == 1)
        {
            // 打开可控硅
            _pb3 = 1;
        }    
        timer1_stop();        
    }

    
}

void int_init(void)
{
    _pbc5 = 1;
    _integ1 = 1;  //双边沿触发
    _integ0 = 1;
    _inte = 1;  //外部中断使能
}

void __attribute((interrupt(0x04))) int_isr(void)
{
    _intf = 0;
    xzero.zero_in_now = _pa3;
    if (xzero.zero_in_now == 0 && xzero.zero_in_last == 1)   //下降沿过零
    {
        timer1_start(238, 0, 1);   //10ms / 76us  = 131.57
    }
        
    else if (xzero.zero_in_now == 1 && xzero.zero_in_last == 0)  //上升沿过零
    {
        timer1_start(238, 0, 1);
    }

    xzero.zero_in_last = _pa3;
}
