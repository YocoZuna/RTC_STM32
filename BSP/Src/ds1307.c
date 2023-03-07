#include "ds1307.h"
#include <stdio.h>
#include "main.h"

void ds1307_init(I2C_HandleTypeDef* i2c);
void ds1307_get_time(I2C_HandleTypeDef* i2c,DS1307_Time_t* getTime);
void ds1307_get_date(I2C_HandleTypeDef* i2c,DS1307_Date_t* date);
void ds1307_set_time(I2C_HandleTypeDef* i2c,DS1307_Time_t* time);
void ds1307_set_date(I2C_HandleTypeDef* i2c,DS1307_Date_t* date);
void display_Time(DS1307_Time_t time);
void display_Date(DS1307_Date_t date);
static uint8_t bcd_to_bin(uint8_t value);
static uint8_t bin_to_bcd(uint8_t value);

#define debug

#ifdef debug
	extern void initialise_monitor_handles(void);
#endif

void ds1307_init(I2C_HandleTypeDef* i2c)
{
#ifdef debug
  initialise_monitor_handles();
#endif
  HAL_StatusTypeDef ds1307Status;
  ds1307Status = HAL_I2C_IsDeviceReady(i2c, DS1307_I2C_ADDR, 1, 100);
  if (ds1307Status != HAL_OK)
  {
#ifdef debug
	  	  printf("DS1307 failed initialiation\n");
#endif
  }

}

void ds1307_set_time(I2C_HandleTypeDef* i2c,DS1307_Time_t* time)
{

	uint8_t sec,min,hrs,ampm;
	//Converting values to bcd
	sec = bin_to_bcd(time->sec);
	min = bin_to_bcd(time->min);
	hrs = bin_to_bcd(time->hrs);
	ampm = bin_to_bcd(time->amPM);

	if(ampm == 1)
	{
		// Setting AMPPM format
		HAL_I2C_Mem_Write_IT(i2c, DS1307_I2C_ADDR, DS1307_ADDR_HRS,1, &ampm, 1);
	}

	HAL_I2C_Mem_Write_IT(i2c, DS1307_I2C_ADDR, DS1307_ADDR_HRS, 1,&hrs, 1);
	HAL_I2C_Mem_Write_IT(i2c, DS1307_I2C_ADDR, DS1307_ADDR_MIN, 1,&min, 1);
	sec &=~(1<<7); // Enabling oscilator
	HAL_I2C_Mem_Write_IT(i2c, DS1307_I2C_ADDR, DS1307_ADDR_SEC, 1, &sec, 1);

}


void ds1307_get_time(I2C_HandleTypeDef* i2c,DS1307_Time_t* getTime)
{
	uint8_t sec,min,hrs,ampm;
	//Converting values to bcd


	HAL_I2C_Mem_Read_IT(i2c, DS1307_I2C_ADDR, DS1307_ADDR_SEC, 1, &sec, 1);
	HAL_I2C_Mem_Read_IT(i2c, DS1307_I2C_ADDR, DS1307_ADDR_MIN, 1, &min, 1);
	HAL_I2C_Mem_Read_IT(i2c, DS1307_I2C_ADDR, DS1307_ADDR_HRS, 1, &hrs, 1);
	if ((hrs >> 6) == 1)
	{
		// TODO
	}
	else
	{
		hrs = bcd_to_bin(hrs);
	}
	


	getTime->sec = bcd_to_bin(sec);
	getTime->min = bcd_to_bin(min);
	getTime->hrs = hrs;
}

static uint8_t bin_to_bcd(uint8_t value)
{
	uint8_t tmp1,tmp2;
	if (value>=10)
	{
		tmp1 = value /10;
		tmp2 = value % 10;

		return ((tmp1<<4)|tmp2);
	}
	return value;
}

static uint8_t bcd_to_bin(uint8_t value)
{
	uint8_t tmp1,tmp2;
	tmp1 = ((value>>4)*10);
	tmp2 = value & (uint8_t)0x0F;
	return tmp1 + tmp2;
}


void display_Time(DS1307_Time_t time)
{
#ifdef debug
	printf("%d:%d:%d\n",time.hrs,time.min,time.sec);
#endif
}

void ds1307_set_date(I2C_HandleTypeDef* i2c,DS1307_Date_t* date)
{
	// Year is type uint8 because RTC can stroe only to last didigts of the year
	uint8_t day,cday,month,year;
	day = bin_to_bcd(date->day);
	cday = bin_to_bcd(date->date);
	month = bin_to_bcd(date->month);
	year = bin_to_bcd(date->year);
	HAL_I2C_Mem_Write_IT(i2c, DS1307_I2C_ADDR, DS1307_ADDR_DAY, 1,&day, 1);
	HAL_I2C_Mem_Write_IT(i2c, DS1307_I2C_ADDR, DS1307_ADDR_DATE, 1,&cday, 1);
	HAL_I2C_Mem_Write_IT(i2c, DS1307_I2C_ADDR, DS1307_ADDR_MONTH, 1,&month, 1);
	HAL_I2C_Mem_Write_IT(i2c, DS1307_I2C_ADDR, DS1307_ADDR_YEAR, 1,&year, 1);

}

void ds1307_get_date(I2C_HandleTypeDef* i2c,DS1307_Date_t* date)
{
	uint8_t day,cday,month,year;
	HAL_I2C_Mem_Read_IT(i2c, DS1307_I2C_ADDR, DS1307_ADDR_DAY, 1,&day, 1);
	HAL_I2C_Mem_Read_IT(i2c, DS1307_I2C_ADDR, DS1307_ADDR_DATE, 1,&cday, 1);
	HAL_I2C_Mem_Read_IT(i2c, DS1307_I2C_ADDR, DS1307_ADDR_MONTH, 1,&month, 1);
	HAL_I2C_Mem_Read_IT(i2c, DS1307_I2C_ADDR, DS1307_ADDR_YEAR, 1,&year, 1);

	date->day = bcd_to_bin(day);
	date->date = bcd_to_bin(cday);
	date->month = bcd_to_bin(month);
	date->year = bcd_to_bin(year);
}

void display_Date(DS1307_Date_t date)
{
	#ifdef debug
			printf("%d  %d.%d.%d\n",date.date,date.day,date.month,date.year);
	#endif
}

