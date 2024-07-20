/*
 * @Author: sidianneng bbear_mail@163.com
 * @Date: 2024-07-20 12:20:52
 * @LastEditors: sidianneng bbear_mail@163.com
 * @FilePath: \Core\Inc\i2c_slave.c
 * @Description: i2c slave protocol drvier
 */

#include "i2c_slave.h"

struct I2c_Slave_Pack i2c_slave_pack;
struct Lcd_Data_Pack lcd_data_pack; 

uint8_t Get_Temperature(void)
{
	return 0;
}

uint8_t Get_Humidity(void)
{
	return 0;
}

uint8_t Get_Smile(void)
{
	return 0;
}

uint8_t Get_Ble(void)
{
	return 0;
}

enum Temp_Format Get_Temp_Format(void)
{
	return 0;
}

uint8_t Get_Battery(void)
{
	return 0;
}
