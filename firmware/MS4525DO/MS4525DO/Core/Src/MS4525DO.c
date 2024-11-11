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
void MS4525DO_assignI2C(I2C_HandleTypeDef *hi2c_device) {
	MS4525DO_i2c_port = hi2c_device;
}
void read_MS4525DO(){
	uint8_t data_buffer[4]; //data buffer to store raw I2C data
	HAL_StatusTypeDef status=HAL_I2C_Master_Receive(MS4525DO_i2c_port, ADDRESS_I2C_MS4525DO << 1, data_buffer, sizeof(data_buffer), HAL_MAX_DELAY);
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

    uint32_t error = HAL_I2C_GetError(MS4525DO_i2c_port);
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
    printf("%u, ",data_buffer[0]);
    printf("%u, ",data_buffer[1]);
    printf("%u, ",data_buffer[2]);
    printf("%u \r\n",data_buffer[3]);
#endif
}

void I2C_ManualBusReset(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Configure SCL and SDA as GPIO outputs
    GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7; // Assuming PB6 (SCL) and PB7 (SDA)
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Toggle SCL 10 times
    for (int i = 0; i < 10; i++) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
        HAL_Delay(1);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
        HAL_Delay(1);
    }

    // Reinitialize I2C
    MX_I2C1_Init();
}

