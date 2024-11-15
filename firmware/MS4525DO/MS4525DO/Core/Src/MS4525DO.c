/*
 * MS4525DO.c
 *
 *  Created on: Oct 26, 2024
 *      Author: chant
 */
#include "MS4525DO.h"

// Use the handle for the UART you configured (e.g., huart2)
extern UART_HandleTypeDef huart1;

int _write(int file, char *data, int len) {
    // Transmit data via UART
    HAL_UART_Transmit(&huart1, (uint8_t*)data, len, HAL_MAX_DELAY);
    return len;
}
/*
 * GLOBAL*/
I2C_HandleTypeDef *MS4525DO_i2c_port;

/**
 * Configures which i2c port MS4525DO is on
 */
void MS4525DO_Initialize(struct MS4525DO_t *pSensor, I2C_HandleTypeDef *hi2c) {
	/*Set i2c handle*/
	pSensor->i2c_handle = hi2c;
	/*Initialize everything to defaults*/
	pSensor->verified = 0;
	SensorStatus initStatus = normal;
	pSensor->sensor_status = initStatus;
	pSensor->raw_data.pressure = 0;
	pSensor->raw_data.temperature = 0;
	pSensor->processed_data.pressure_psi = 0;
	pSensor->processed_data.temperature_C = 0;
	pSensor->processed_data.airspeed_mps = 0;
	pSensor->processed_data.airspeed_calibrated_mps = 0;
}
void read_MS4525DO(struct MS4525DO_t *pSensor) {
	uint8_t data_buffer[4]; //data buffer to store raw I2C data
	HAL_StatusTypeDef status = HAL_I2C_Master_Receive(pSensor->i2c_handle, ADDRESS_I2C_MS4525DO << 1, data_buffer, sizeof(data_buffer), HAL_MAX_DELAY);
#ifdef VERBOSE_MODE_EN
    if (status == HAL_OK) {
        printf("HAL_OK\r\n");
    } else if (status == HAL_ERROR) {
    	printf("HAL_ERROR\r\n");
    } else if (status == HAL_BUSY) {
    	printf("HAL_BUSY\r\n");
    } else if (status == HAL_TIMEOUT) {
        printf("HAL_TIMEOUT\r\n");
    }
    //diagnose HAL error
    uint32_t error = HAL_I2C_GetError(pSensor->i2c_handle);
    if (error == HAL_I2C_ERROR_NONE) {
      printf("no errors \r\n");
    } else if (error == HAL_I2C_ERROR_BERR) {
      printf("HAL_I2C_ERROR_BERR\r\n");
    } else if (error == HAL_I2C_ERROR_ARLO) {
      printf("HAL_I2C_ERROR_ARLO\r\n");
    } else if (error == HAL_I2C_ERROR_AF) {
      printf("HAL_I2C_ERROR_AF\r\n");
    } else if (error == HAL_I2C_ERROR_OVR) {
      printf("HAL_I2C_ERROR_OVR\r\n");
    } else if (error == HAL_I2C_ERROR_DMA) {
      printf("HAL_I2C_ERROR_DMA\r\n");
    } else if (error == HAL_I2C_ERROR_TIMEOUT) {
      printf("HAL_I2C_ERROR_TIMEOUT\r\n");
    }
    //print the raw bytes
    printf("%u, ",data_buffer[0]);
    printf("%u, ",data_buffer[1]);
    printf("%u, ",data_buffer[2]);
    printf("%u \r\n",data_buffer[3]);
#endif

//    pData->sensor_status = 1;
   pSensor->processed_data.airspeed_mps = 12;
    printf("%f \r\n",pSensor->processed_data.airspeed_mps);
}


