/*
 * @Author: sidianneng bbear_mail@163.com
 * @Date: 2024-07-20 12:20:52
 * @LastEditors: sidianneng bbear_mail@163.com
 * @FilePath: \Core\Inc\i2c_slave.c
 * @Description: i2c slave protocol drvier
 */

#include "i2c_slave.h"

#define TEMP_H 13 
#define TEMP_T 13
#define TEMP_S 11
#define TEMP_D 9
#define SMILE  7
#define BLE    7
#define T_FOR  7 
#define HUMI_T 5
#define BAT    5
#define HUMI_S 3

uint8_t num_buf[] = {0xf5, 0x05, 0xd3, 0x97, 0x27, 0xb6, 0xf6, 0x15, 0xf7, 0xb7};

static float Get_Temperature(struct I2c_Slave_Pack* i2c_slave_pack)
{
	uint8_t hunderd = 0;
	uint8_t ten = 0;
	uint8_t single = 0;
	uint8_t decimal = 0;
	uint8_t i;
	if(!i2c_slave_pack)
		return -1;

	if(i2c_slave_pack->raw_data[TEMP_H] & 0x08)
		hunderd = 1;

	for(i = 0;i < sizeof(num_buf); i++) {
		if((i2c_slave_pack->raw_data[TEMP_T] & (~0x08)) == num_buf[i])
			break;
	}	
	ten = i;

	for(i = 0;i < sizeof(num_buf); i++) {
		if((i2c_slave_pack->raw_data[TEMP_S] & (~0x08)) == num_buf[i])
			break;
	}	
	single = i;

	for(i = 0;i < sizeof(num_buf); i++) {
		if((i2c_slave_pack->raw_data[TEMP_D] & (~0x08)) == num_buf[i])
			break;
	}	
	decimal = i;

	return (hunderd * 100 + ten * 10 + single + decimal * 0.1);
}

static int8_t Get_Humidity(struct I2c_Slave_Pack* i2c_slave_pack)
{
	uint8_t ten, single = 0;
	uint8_t i;
	if(!i2c_slave_pack)
		return -1;

	for(i = 0;i < sizeof(num_buf); i++) {
		if((i2c_slave_pack->raw_data[HUMI_T] & (~0x08)) == num_buf[i])
			break;
	}	
	ten = i;

	for(i = 0;i < sizeof(num_buf); i++) {
		if((i2c_slave_pack->raw_data[HUMI_S] & (~0x08)) == num_buf[i])
			break;
	}	
	single = i;

	return (ten * 10 + single);
}

//0=off, 1=happy, 2=sad
static int8_t Get_Smile(struct I2c_Slave_Pack* i2c_slave_pack)
{
	if(!i2c_slave_pack)
		return -1;
	
	if((i2c_slave_pack->raw_data[SMILE] & (~0xf8)) == 0x00)
		return 0;
	else if((i2c_slave_pack->raw_data[SMILE] & (~0xf8)) == 0x05)
		return 1;
	else if((i2c_slave_pack->raw_data[SMILE] & (~0xf8)) == 0x06)
		return 2;

	return -2;
}

//0=off, 1=on
static int8_t Get_Ble(struct I2c_Slave_Pack* i2c_slave_pack)
{
	if(!i2c_slave_pack)
		return -1;

	if(i2c_slave_pack->raw_data[BLE] & (0x01 << 4))
		return 1;
	else
		return 0;
}

static enum Temp_Format Get_Temp_Format(struct I2c_Slave_Pack* i2c_slave_pack)
{
	if(!i2c_slave_pack)
		return -1;

	if(i2c_slave_pack->raw_data[T_FOR] & (0x01 << 6))
		return Fahrenheit;
	else
		return Celsius;
}

//0=off, 1=on
static int8_t Get_Battery(struct I2c_Slave_Pack* i2c_slave_pack)
{
	if(!i2c_slave_pack)
		return -1;

	if(i2c_slave_pack->raw_data[BAT] & (0x01 << 3))
		return 1;
	else
		return 0;
}

int8_t Update_Lcd_Data(struct I2c_Slave_Pack* i2c_slave_pack, struct Lcd_Data_Pack* lcd_data_pack)
{
	if(!i2c_slave_pack || !lcd_data_pack)
	       return -1;	

	lcd_data_pack->temp = Get_Temperature(i2c_slave_pack);
	if(lcd_data_pack->temp < 0) return -2;
	lcd_data_pack->humi = Get_Humidity(i2c_slave_pack);
	if(lcd_data_pack->humi < 0) return -3;
	lcd_data_pack->smile = Get_Smile(i2c_slave_pack);
	if(lcd_data_pack->smile < 0) return -4;
	lcd_data_pack->ble = Get_Ble(i2c_slave_pack);
	if(lcd_data_pack->ble < 0) return -5;
	lcd_data_pack->temp_format = Get_Temp_Format;
	if(lcd_data_pack->temp_format < 0) return -6;
	lcd_data_pack->battery = Get_Battery(i2c_slave_pack);
	if(lcd_data_pack->battery < 0) return -7;

	return 0;
}
