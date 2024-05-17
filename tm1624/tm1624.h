#ifndef __LCD_H__
#define __LCD_H__


#include "main.h"
extern unsigned int dLcdDisplayData[8];

#define SEG_A 0x0001
#define SEG_B 0x0002
#define SEG_C 0x0004
#define SEG_D 0x0008
#define SEG_E 0x0010
#define SEG_F 0x0020
#define SEG_G 0x0040
#define SEG_H 0x0080
#define SEG_I 0x0100

//TODO在这里完成接口对接
/* -------------------------------------------------------------------------- */
#define  LCD_DIO_GPIO_PIN   
#define  LCD_CLK_GPIO_PIN   
#define  LCD_STB_GPIO_PIN   


#define  LCD_DIO_GPIO_DIRECTION  
#define  LCD_CLK_GPIO_DIRECTION  
#define  LCD_STB_GPIO_DIRECTION  


#define  LCD_DIO_GPIO_PULLUP     
#define  LCD_CLK_GPIO_PULLUP     
#define  LCD_STB_GPIO_PULLUP     

#define  LCD_STB_OUTPUT_HIGH     
#define  LCD_STB_OUTPUT_LOW      


#define  LCD_CLK_OUTPUT_HIGH     
#define  LCD_CLK_OUTPUT_LOW      

#define  LCD_DIO_OUTPUT_HIGH     
#define  LCD_DIO_OUTPUT_LOW      
/* -------------------------------------------------------------------------- */

#define  char_0     0
#define  char_1     1
#define  char_2     2
#define  char_3     3
#define  char_4     4
#define  char_5     5
#define  char_6     6
#define  char_7     7
#define  char_8     8
#define  char_9     9
#define  char_A     10
#define  char_C     11
#define  char_E     12
#define  char_H     13
#define  char_L     14
#define  char_r     15
#define  char_o     16
#define  char_Null  17


#define LCD_SKIN_L1               (dLcdDisplayData[3] |= SEG_I)
#define LCD_SKIN_L2               (dLcdDisplayData[2] |= SEG_I)
#define LCD_SKIN_L3               (dLcdDisplayData[0] |= SEG_I)
#define LCD_SKIN_L4               (dLcdDisplayData[0] |= SEG_G)
#define LCD_SKIN_L5               (dLcdDisplayData[0] |= SEG_F)
#define LCD_SKIN_L6               (dLcdDisplayData[0] |= SEG_E)
#define LCD_SKIN_L7               (dLcdDisplayData[0] |= SEG_D)
#define LCD_SKIN_L8               (dLcdDisplayData[0] |= SEG_C)

#define LCD_KEY_MAN1			  (dLcdDisplayData[2] |= SEG_H)
#define LCD_KEY_MAN2			  (dLcdDisplayData[3] |= SEG_H)
#define LCD_KEY_MAN3			  (dLcdDisplayData[4] |= SEG_H)
#define LCD_KEY_MAN4			  (dLcdDisplayData[5] |= SEG_H)
#define LCD_KEY_MAN5			  (dLcdDisplayData[6] |= SEG_H)
#define LCD_KEY_FEM1   			  (dLcdDisplayData[0] |= SEG_H)
#define LCD_KEY_FEM2   			  (dLcdDisplayData[1] |= SEG_H)
#define LCD_KEY_FEM3   			  (dLcdDisplayData[6] |= SEG_I)
#define LCD_KEY_FEM4   			  (dLcdDisplayData[0] |= SEG_A)
#define LCD_KEY_FEM5   			  (dLcdDisplayData[0] |= SEG_B)

#define LCD_LINK1     			  (dLcdDisplayData[4] |= SEG_I)
#define LCD_LINK2     			  (dLcdDisplayData[5] |= SEG_I)

#define LCD_POWER1    			  (dLcdDisplayData[3] |= SEG_F)
#define LCD_POWER2    			  (dLcdDisplayData[2] |= SEG_G)

typedef struct 
{
    unsigned int num_temp;
    unsigned char icon_cold :1;
    unsigned char icon_mid :1;
    unsigned char icon_hot;
    unsigned char icon_unit;

} display_buff_T;
extern display_buff_T display_buff;
void TM1624_Init(void);
void TM1624_WRITE_ORDER(unsigned char  DATA);
void TM1624_WRITE_BYTE(unsigned char DATA);
void LcdDisplayClear(void);
void LcdDisplayUpdate(void);
void Delay_us(unsigned char DATA);
void LED_init(void);
void LED_disp_test(void);
void DISPLAY_buf(void);//100ms
void LED_disp(unsigned char display_control);
#endif

