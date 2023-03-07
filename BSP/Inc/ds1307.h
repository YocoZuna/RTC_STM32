
#ifndef INC_DS1307_H_
#define INC_DS1307_H_
#include <stdint.h>
#include "main.h"

#define DS1307_I2C_ADDR             (0x68<<1)


#define Monday						1
#define Tuesday						2
#define Wendsday					3
#define Thursday					4
#define Friday						5
#define Saturday					6
#define Sunday						7

#define DS1307_TIME_FORMAT_12_AM    0
#define DS1307_TIME_FORMAT_12_PM    1    
#define DS1307_TIME_FORMAT_24       2

#define DS1307_ADDR_SEC             0x00
#define DS1307_ADDR_MIN             0x01
#define DS1307_ADDR_HRS             0x02
#define DS1307_ADDR_DAY             0x03
#define DS1307_ADDR_DATE            0x04
#define DS1307_ADDR_MONTH           0x05
#define DS1307_ADDR_YEAR            0x06


typedef struct 
{
    uint8_t sec;
    uint8_t min;
    uint8_t hrs;
    uint8_t amPM;
}DS1307_Time_t;

typedef struct 
{
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint8_t year;
}DS1307_Date_t;

void ds1307_init(I2C_HandleTypeDef* i2c);
void ds1307_get_time(I2C_HandleTypeDef* i2c,DS1307_Time_t* getTime);
void ds1307_get_date(I2C_HandleTypeDef* i2c,DS1307_Date_t* date);
void ds1307_set_time(I2C_HandleTypeDef* i2c,DS1307_Time_t* time);
void ds1307_set_date(I2C_HandleTypeDef* i2c,DS1307_Date_t* date);
void display_Time(DS1307_Time_t time);
void display_Date(DS1307_Date_t date);
#endif 
