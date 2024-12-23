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

/*Includes*/
#include "stm32f1xx_hal.h" /* Needed for I2C */
#include <math.h>
#include <stdio.h>

/*MACRO DEFINITIONS*/
/*MS4525DO CONFIGURATION PARAMETERS*/
#define TYPE_MS4525DO     		(bool)     0 /*1 - Type A, 0 - Type B*/
#define PMAX_PSI_MS4525DO 		(double)   1 //casted to double for transfer function
#define PMIN_PSI_MS4525DO 		(double)   -1
#define ADDRESS_I2C_MS4525DO 	(uint8_t) 0x46
/*PROCESSING MACROS*/
#define AIR_DENSITY			 	(double) 1.225 //kg/m^3
//this is where to include the calibration macros if needed, to generalize wind tunnel calibration process

/*STRUCTURES AND ENUMERATORS*/
/*MS4525DO Sensor Package*/
struct data_t {
	uint8_t status;
    struct raw_t {
        uint16_t pressure;
        uint16_t temperature;
    } raw;
    /*Processed data - underwent conversions to engineering values and calibrations*/
    struct processed_t {
        double pressure_psi; /*range: [-1,1], steps at  */
        double temperature_C; /*range: []*/
        double airspeed_ms; /*range: */
    } processed;
};
/*Enumerate status codes returned by the MS4525DO*/
enum Status {
	normal,
	reserved,
	stale,
	fault
};

/*Updates the MS4525DO sensor data*/
void update_MS4525DO_data();

/*Fetches the current MS4525DO sensor data*/
struct data_t fetch_MS4525DO_data();


/*Lower Level Functions - I2C, CAN*/



#endif /* INC_MS4525DO_H_ */
