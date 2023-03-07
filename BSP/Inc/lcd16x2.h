#ifndef INC_LCD16X2_H_
#define INC_LCD16X2_H_

#include "main.h"
#include <stdint.h>

#define LCD_CMD_4L_2N_5X8F				0x28
#define LCD_CMD_DISPLAY_ON_CURSOR_ON	0x0E
#define LCD_COM_RAM_INCREMENT			0x06
#define LCD_DISPLAY_CLEAR				0x01
#define LCD_CMD_DISPLAY_RETURN_HOME		0x02


void lcd_init(void);
void lcd_send_4bits(uint8_t data);
void lcd_send_cmd(uint8_t cmd);
void lcd_print_string(char *msg);

void lcd_send_char(uint8_t cmd);
#endif
