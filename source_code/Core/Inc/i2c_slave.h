/*
 * @Author: sidianneng bbear_mail@163.com
 * @Date: 2024-07-20 12:20:52
 * @LastEditors: sidianneng bbear_mail@163.com
 * @FilePath: \Core\Inc\i2c_slave.h
 * @Description: i2c slave protocol drvier
 */

#ifndef I2C_SLAVE_H
#define I2C_SLAVE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define RAW_DATA_MAX_LEN 24

struct I2c_Slave_Pack {
	uint8_t raw_data[RAW_DATA_MAX_LEN];
	uint8_t raw_data_len;
};

enum Temp_Format {
	Celsius = 0,
	Fahrenheit,
};

struct Lcd_Data_Pack {
	float temp;
	int8_t humi;
	int8_t smile;
	int8_t ble; 
	int8_t temp_format;
	int8_t battery;
};

int8_t Update_Lcd_Data(struct I2c_Slave_Pack* i2c_slave_pack, struct Lcd_Data_Pack* lcd_data_pack);

#ifdef __cplusplus
}
#endif

#endif
