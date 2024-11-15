/*
 * MS4525DO.h
 *
 *  Created on: Oct 26, 2024
 *      Author: chant
 */

//Datasheet: https://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FMS4525DO%7FB10%7Fpdf%7FEnglish%7FENG_DS_MS4525DO_B10.pdf%7FCAT-BLPS0002
/*Differential Pressure Transducer Used for 2024/2025 (PN): MS4525DO-DS3BK001DPL*/

#ifndef INC_MS4525DO_H_
#define INC_MS4525DO_H_

#include "stm32f1xx_hal.h" /* Needed for I2C */
#include <math.h>
#include <stdio.h>
#include <stdbool.h> // Provides bool, true, and false

/*MS4525DO CONFIGURATION PARAMETERS*/
#define TYPE_MS4525DO     		(bool)     0 /*1 - Type A, 0 - Type B*/
#define PMAX_PSI_MS4525DO 		(double)   1 //casted to double for transfer function
#define PMIN_PSI_MS4525DO 		(double)   -1
#define ADDRESS_I2C_MS4525DO 	(uint8_t) 0x46
#define AIR_DENSITY			 	(double) 1.225 //kg/m^3

#define VERBOSE_MODE_EN //uncomment to enable verbose debug mode
#define WIND_TUNNEL_EN //uncomment to enable wind tunnel calibration features (enabled during wind tunnel only)
#define PRINTF_OVERLOAD //uncomment to have printf print to serial

/*Raw bytes*/
struct raw_t {
	uint16_t pressure;
	uint16_t temperature;
};
/*Processed Data*/
struct processed_t {
	double pressure_psi; /*range: [-1,1]*/
	double temperature_C; /*range: []*/
	double airspeed_mps; /*range: */
	double airspeed_calibrated_mps;
};
/*I2C read status codes - see MS4525DO interface manual*/
typedef enum {
	normal,
	reserved,
	stale,
	fault
} SensorStatus;

struct MS4525DO_t {
	I2C_HandleTypeDef *i2c_handle;
	bool verified;
	SensorStatus sensor_status;
	struct raw_t raw_data;
	struct processed_t processed_data;
};
#ifdef PRINTF_OVERLOAD
int _write(int file, char *data, int len); //An overload so printf() can be associated with serial print
#endif

void MS4525DO_Initialize(struct MS4525DO_t *pSensor, I2C_HandleTypeDef *hi2c);
void read_MS4525DO(struct MS4525DO_t *pData);

#endif /* INC_MS4525DO_H_ */
