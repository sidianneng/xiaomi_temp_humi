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
	uint8_t temp;
	uint8_t humi;
	uint8_t smile;
	uint8_t ble; 
	enum Temp_Format temp_format;
	uint8_t battery;
};

uint8_t Get_Temperature(void);
uint8_t Get_Humidity(void);
uint8_t Get_Smile(void);
uint8_t Get_Ble(void);
enum Temp_Format Get_Temp_Format(void);
uint8_t Get_Battery(void);

#ifdef __cplusplus
}
#endif

#endif
