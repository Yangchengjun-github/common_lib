
#include "tm1624.h"


#define TM1624_DELAY 3
display_buff_T display_buff = {0};
unsigned int dLcdDisplayData[8];

unsigned int const TableNumber[] =
{
    SEG_A + SEG_B + SEG_C + SEG_D + SEG_E + SEG_F, //0
    SEG_B + SEG_C,                         //1
    SEG_A + SEG_B + SEG_D + SEG_E + SEG_G, //2
    SEG_A + SEG_B + SEG_C + SEG_D + SEG_G, //3
    SEG_B + SEG_C + SEG_F + SEG_G,         //4
    SEG_A + SEG_C + SEG_D + SEG_F + SEG_G, //5
    SEG_A + SEG_C + SEG_D + SEG_E + SEG_F + SEG_G, //6
    SEG_A + SEG_B + SEG_C,               //7
    SEG_A + SEG_B + SEG_C + SEG_D + SEG_E + SEG_F + SEG_G, //8
    SEG_A + SEG_B + SEG_C + SEG_D + SEG_F + SEG_G, //9
    SEG_A + SEG_B + SEG_C + SEG_E + SEG_F + SEG_G, //A
    SEG_A + SEG_D + SEG_E + SEG_F,        //C
    SEG_A + SEG_D + SEG_E + SEG_F + SEG_G, //E
    SEG_B + SEG_C + SEG_E + SEG_F + SEG_G, //H
    SEG_D + SEG_E + SEG_F,                //L
    SEG_E + SEG_G,                        //r
    SEG_C + SEG_D + SEG_E + SEG_G,        //o
    0x0000,                               //空
};




void TM1624_Init(void)
{
	u8 i;
/* -------------------------------------------------------------------------- */
//在这里完成你的IO初始化



/* -------------------------------------------------------------------------- */
    TM1624_WRITE_ORDER(0x03);		   // 
    TM1624_WRITE_ORDER(0x40);		   // 地址递增，写数据
    TM1624_WRITE_ORDER(0xC0);		   // 地址设置
    for(i = 0; i < 14; i++)
    {
        TM1624_WRITE_BYTE(0x00);	   //
    }
    TM1624_WRITE_ORDER(0x8C);		   //
}



//写命令到TM1624
void TM1624_WRITE_ORDER(unsigned char  DATA)
{
    LCD_STB_OUTPUT_HIGH;
    Delay_us(TM1624_DELAY);     //LCD_WAIT_DELAY;
    LCD_CLK_OUTPUT_LOW;
    LCD_DIO_OUTPUT_LOW;
    LCD_STB_OUTPUT_LOW;
    TM1624_WRITE_BYTE(DATA);
    LCD_CLK_OUTPUT_HIGH;

}

//写一个字节到TM1624
void TM1624_WRITE_BYTE(unsigned char DATA)
{
    unsigned char  	i;
    for(i = 8; i != 0; i--)
    {
        LCD_CLK_OUTPUT_LOW;
        Delay_us(TM1624_DELAY);
        if(DATA & 0x01)
        {
            LCD_DIO_OUTPUT_HIGH;
        }
        else
        {
            LCD_DIO_OUTPUT_LOW;  
        }
        Delay_us(TM1624_DELAY);
        DATA >>= 1;
        LCD_CLK_OUTPUT_HIGH;
        Delay_us(TM1624_DELAY);
        Delay_us(TM1624_DELAY);
    }

}

void LcdDisplayClear(void)
{
    unsigned char i;
    for(i = 0; i < 0x08; i++)
    {
        dLcdDisplayData[i] = 0x00;
    }
}


//========================================
void LcdDisplayUpdate(void)
{
    unsigned char i;
    unsigned char temp = 0;

    TM1624_WRITE_ORDER(0x00);		   // 
    TM1624_WRITE_ORDER(0x40);		   //地址递增，写数据
    TM1624_WRITE_ORDER(0xC0);		   //地址设置 0XC0
    for(i = 0; i < 0x07; i++)
    {
        //	TM1624_WRITE_BYTE(0xff);	   // 更新数据
        temp = (unsigned char)(dLcdDisplayData[i] & 0xff);
        TM1624_WRITE_BYTE(temp);	   // 更新数据
        temp = (unsigned char)(dLcdDisplayData[i] >> 8);
        TM1624_WRITE_BYTE(temp);	   // 更新数据
    }
    TM1624_WRITE_ORDER(0x8C);		   // 打开显示，调节亮度
}
//==========================================


//=======================================
void Delay_us(unsigned char DATA)
{
	return ;
    volatile unsigned char CNT;
    for(CNT = 0; CNT < DATA; CNT++);
}

//===============================
void LED_init()
{
    TM1624_Init();
    LcdDisplayClear();
    LcdDisplayUpdate();

}


void LED_disp_test(void)
{
	unsigned char i;
	
    LcdDisplayClear();
    
    for(i = 0; i < 0x08; i++)   
    {
        dLcdDisplayData[i] = 0x0;
		
    }
	dLcdDisplayData[0] = 0x01;
	dLcdDisplayData[1] = 0x02;
    
    LcdDisplayUpdate();
}

void LED_disp(uint8_t display_control)
{
	unsigned char data_value = 0;
	unsigned char i;
	LcdDisplayClear();
	for(i = 0; i < 0x08; i++)   
	{
		dLcdDisplayData[i] = 0x0;
	}
	if(display_control == 0)   //全部熄灭
	{
		for(i = 0; i < 0x04; i++)   
		{
			dLcdDisplayData[i] = TableNumber[17];
		}
		LcdDisplayUpdate();
		printf("---LED_disp---\n");
		return ;
	}
	data_value = (unsigned char)((display_buff.num_temp / 100) % 10);
	dLcdDisplayData[3] = TableNumber[data_value];

	data_value = (unsigned char)((display_buff.num_temp / 10) % 10);
	dLcdDisplayData[2] = TableNumber[data_value];

	data_value = (unsigned char)(display_buff.num_temp % 10);
	dLcdDisplayData[1] = TableNumber[data_value];
	
	if(display_buff.icon_cold)
	{
		dLcdDisplayData[0] |= SEG_A;
	}
	else
	{
		;
	}
	if(display_buff.icon_mid)
	{
		dLcdDisplayData[0] |= SEG_B;
	}
	else
	{
		;
	}
	if(display_buff.icon_hot)
	{
		dLcdDisplayData[0] |= SEG_C;
	}
	else
	{
		;
	}
	if(display_buff.icon_unit)
	{
		dLcdDisplayData[0] |= SEG_D;
	}
	else
	{
		;
	}
	
	LcdDisplayUpdate();
}

#if 0
void DISPLAY_buf(void)//100ms
{
	volatile static u8 Cut_FLASH_time = 0;
	u8 data_value = 0;
	
	LcdDisplayClear();
	P_LED_POWER = 1;
	
    if(++Cut_FLASH_time>5)
    {
    	F_LCD_FLAH = ~F_LCD_FLAH;
    	Cut_FLASH_time = 0;
    }
    
	if(SYS_STATE == sys_standby)
	{
		if(F_LCD_FLAH)
		{
		   P_LED_POWER = 0;
		}
	}
	else if(SYS_STATE == sys_work)
	{
		if(F_LINK_EN)
		{
			LCD_LINK1;
			LCD_LINK2;
		}
		
		if(((F_TOUCH_KEY)&&(F_SKIN_OK)&&(F_LAMP_DELAY_OK)))
		{
			F_LINK_READY = 1;
			P_LED_POWER = 0;
		}
		
	    if(WORK_MODE == WORK_MODE_MAN)
		{
			LCD_KEY_MAN1;
			LCD_KEY_MAN2;
			LCD_KEY_MAN3;
			LCD_KEY_MAN4;
			LCD_KEY_MAN5;
		}
		else if(WORK_MODE == WORK_MODE_FEM)
		{
			LCD_KEY_FEM1; 
			LCD_KEY_FEM2; 
			LCD_KEY_FEM3; 
			LCD_KEY_FEM4; 
			LCD_KEY_FEM5; 
		}
		else
		{
			;
		}
		


		data_value = (unsigned char)(num_temp / 100000);
        dLcdDisplayData[6] |= TableNumber[data_value];  //

        data_value = (unsigned char)((num_temp / 10000) % 10);
        dLcdDisplayData[5] |= TableNumber[data_value];  //

        data_value = (unsigned char)((num_temp / 1000) % 10);
        dLcdDisplayData[4] |= TableNumber[data_value];  //

        data_value = (unsigned char)((num_temp / 100) % 10);
        dLcdDisplayData[3] |= TableNumber[data_value];

        data_value = (unsigned char)((num_temp / 10) % 10);
        dLcdDisplayData[2] |= TableNumber[data_value];

        data_value = (unsigned char)(num_temp % 10);
        dLcdDisplayData[1] |= TableNumber[data_value];
        
		switch(d_lamp_levle)
		{
			case LCD_LEVEL_8:
				LCD_SKIN_L8;
				LCD_SKIN_L7;
				LCD_SKIN_L6;
				LCD_SKIN_L5;
				LCD_SKIN_L4;
		    	LCD_SKIN_L3;
				LCD_SKIN_L2;
				LCD_SKIN_L1;
			break;
			
			case LCD_LEVEL_7:
				LCD_SKIN_L7;
				LCD_SKIN_L6;
				LCD_SKIN_L5;
				LCD_SKIN_L4;
		    	LCD_SKIN_L3;
				LCD_SKIN_L2;
				LCD_SKIN_L1;
			break;
			
			case LCD_LEVEL_6:
				LCD_SKIN_L6;
				LCD_SKIN_L5;
				LCD_SKIN_L4;
		    	LCD_SKIN_L3;
				LCD_SKIN_L2;
				LCD_SKIN_L1;
			break;
			
			case LCD_LEVEL_5:
				LCD_SKIN_L5;
				LCD_SKIN_L4;
		    	LCD_SKIN_L3;
				LCD_SKIN_L2;
				LCD_SKIN_L1;
			break;
			
			case LCD_LEVEL_4:
				LCD_SKIN_L4;
		    	LCD_SKIN_L3;
				LCD_SKIN_L2;
				LCD_SKIN_L1;
			break;
			
			case LCD_LEVEL_3:
		    	LCD_SKIN_L3;
				LCD_SKIN_L2;
				LCD_SKIN_L1;
			break;
			
			case LCD_LEVEL_2:
				LCD_SKIN_L2;
				LCD_SKIN_L1;
			break;
			
			case LCD_LEVEL_1:
				LCD_SKIN_L1;
			break;
		}
	}
	else if(SYS_STATE == sys_error)
	{
	    if(F_NTC_FD_ERROR)
	    {
		    dLcdDisplayData[6] |= TableNumber[char_E];
	        dLcdDisplayData[5] |= TableNumber[char_r];
	        dLcdDisplayData[4] |= TableNumber[char_r];
	        dLcdDisplayData[3] |= TableNumber[char_2];
	        dLcdDisplayData[2] |= TableNumber[char_Null];
	        dLcdDisplayData[1] |= TableNumber[char_Null];
	    }
	    else if(F_NTC_COOL_ERROR)
	    {
	    	dLcdDisplayData[6] |= TableNumber[char_E];
	        dLcdDisplayData[5] |= TableNumber[char_r];
	        dLcdDisplayData[4] |= TableNumber[char_r];
	        dLcdDisplayData[3] |= TableNumber[char_4];
	        dLcdDisplayData[2] |= TableNumber[char_Null];
	        dLcdDisplayData[1] |= TableNumber[char_Null];
	    }
	    else if(F_BOOST_ERROR)
	    {
	    	dLcdDisplayData[6] |= TableNumber[char_E];
	        dLcdDisplayData[5] |= TableNumber[char_r];
	        dLcdDisplayData[4] |= TableNumber[char_r];
	        dLcdDisplayData[3] |= TableNumber[char_3];
	        dLcdDisplayData[2] |= TableNumber[char_Null];
	        dLcdDisplayData[1] |= TableNumber[char_Null];
	    }
	    else if(F_FAN_ERROR)
	    {
	       	dLcdDisplayData[6] |= TableNumber[char_E];
	        dLcdDisplayData[5] |= TableNumber[char_r];
	        dLcdDisplayData[4] |= TableNumber[char_r];
	        dLcdDisplayData[3] |= TableNumber[char_1];
	        dLcdDisplayData[2] |= TableNumber[char_Null];
	        dLcdDisplayData[1] |= TableNumber[char_Null];
	    }
	    
	}
	else 
	{
	    ;
	}
    LcdDisplayUpdate();
}
#endif


