/*
 * lcd16x2.c
 *
 *  Created on: Mar 5, 2023
 *      Author: dawid
 */
#include "main.h"
#include "lcd16x2.h"
/*
This driver uses only 4 data pins to work with LCD in order 
to not wast pins in MCU 
*/
void lcd_init(void);
void lcd_send_4bits(uint8_t data);
void lcd_send_cmd(uint8_t cmd);
void lcd_print_string(char *msg);
void lcd_set_cursor(uint8_t column,uint8_t line);
static void lcd_enable(void);
static void lcd_udelay(uint8_t delay);
void lcd_send_char(uint8_t cmd);
void lcd_init(void)
{

	HAL_Delay(15);
	lcd_send_4bits(0x3);
    HAL_Delay(5);
    GPIOB->ODR ^=((GPIOB->ODR>>12)<<12);
    lcd_send_4bits(0x3);
    lcd_udelay(100);
    GPIOB->ODR ^=((GPIOB->ODR>>12)<<12);
    lcd_send_4bits(0x2);
    // Function set
    HAL_Delay(5);
    GPIOB->ODR ^=((GPIOB->ODR>>12)<<12);
    lcd_send_cmd(LCD_CMD_4L_2N_5X8F);
    HAL_Delay(5);
    //Display On cursor on
    GPIOB->ODR ^=((GPIOB->ODR>>12)<<12);
    lcd_send_cmd(LCD_CMD_DISPLAY_ON_CURSOR_ON);
    HAL_Delay(5);
    GPIOB->ODR ^=((GPIOB->ODR>>12)<<12);
    lcd_send_cmd(LCD_CMD_DISPLAY_RETURN_HOME);
    // Display clear
    HAL_Delay(5);
    GPIOB->ODR ^=((GPIOB->ODR>>12)<<12);
    lcd_send_cmd(LCD_DISPLAY_CLEAR);
    HAL_Delay(5);

    //Entry mode set cmd
    GPIOB->ODR ^=((GPIOB->ODR>>12)<<12);
    lcd_send_cmd(LCD_COM_RAM_INCREMENT);
    HAL_Delay(5);
    GPIOB->ODR ^=((GPIOB->ODR>>12)<<12); // Cleaning all lines ! very important step

}

void lcd_send_4bits(uint8_t data)
{
	/*
	uint8_t tmp;
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, RESET);
	HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, RESET);
	tmp = (data & 0xF0);
	GPIOB->ODR |= (tmp<<12);

	lcd_enable();
	GPIOB->ODR ^= (tmp<<12);
	*/
	GPIOB->ODR |= (((data>>0)&0x1)<<12);
	GPIOB->ODR |= (((data>>1)&0x1)<<13);
	GPIOB->ODR |= (((data>>2)&0x1)<<14);
	GPIOB->ODR |= (((data>>3)&0x1)<<15);
	lcd_enable();
}
void lcd_send_cmd(uint8_t cmd)
{
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, RESET);
	HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, RESET);
	lcd_send_4bits(cmd>>4);
	lcd_send_4bits(cmd&0x0F);
}
static void lcd_enable(void)
{
	HAL_GPIO_WritePin(ENABLE_GPIO_Port, ENABLE_Pin, SET);
	lcd_udelay(100);
	HAL_GPIO_WritePin(ENABLE_GPIO_Port, ENABLE_Pin, RESET);
	lcd_udelay(100);

}
void lcd_print_string(char *msg)
{
	do
	{
		lcd_send_char((uint8_t)*msg++);
		lcd_udelay(100);
	}
	while(*msg !='\0');
}
void lcd_set_cursor(uint8_t column,uint8_t line)
{
/*
 *
 * 00 01 02 03.......... line 1
 * 40 41 42 43			 line 2
 */
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, RESET);
	HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, RESET);

	column--;
	switch (line)
	{
	case 1:
		lcd_send_cmd((column |= 0x80)); // We have to add this cus we want to keep D7 1
		break;
	case 2:
		lcd_send_cmd((column |= 0xC0)); // We have to add this cus we wanto to keep D7 1 and ad4
		break;
	}
}

void lcd_send_char(uint8_t cmd)
{
	GPIOB->ODR ^=((GPIOB->ODR>>12)<<12);
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, SET);
	HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, RESET);

	lcd_send_4bits(cmd>>4);
	GPIOB->ODR ^=((GPIOB->ODR>>12)<<12);
	lcd_send_4bits(cmd&0x0F);
}
static void lcd_udelay(uint8_t delay)
{
	uint16_t udelay = (delay)*100;
	for (int i =0;i<udelay;i++);
}
