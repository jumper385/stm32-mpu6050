/*
 * mpu6050.c
 *
 *  Created on: 20 Aug. 2022
 *      Author: henry
 */

#include "main.h"
#include "mpu6050.h"

HAL_StatusTypeDef MPU6050_Init(MPU6050 *dev, I2C_HandleTypeDef * i2c) {
	dev -> i2c = i2c;

	uint8_t data = 0x00;
	if (HAL_I2C_Mem_Write(dev->i2c, MPU6050_ADDR, 0x6B, 1, &data, 1, 1000) != HAL_OK){
		return HAL_ERROR;
	}

	data = 6 << 3;
	if (HAL_I2C_Mem_Write(dev->i2c, MPU6050_ADDR, 0x1A, 1, &data, 1, 1000) != HAL_OK){
		return HAL_ERROR;
	}

	return HAL_OK;
}

HAL_StatusTypeDef MPU6050_GetTemp(MPU6050 *dev) {
	uint8_t regData[2];
	if (HAL_I2C_Mem_Read(dev->i2c, MPU6050_ADDR, 0x41, 1, &regData, 2, 1000) != HAL_OK) {
		return HAL_ERROR;
	}
	int16_t temp_raw = (regData[0] << 8 | regData[1]);
	dev->temp = (int16_t)temp_raw/340.0 + 36.53;
	return HAL_OK;
}

HAL_StatusTypeDef MPU6050_GetAccel(MPU6050 *dev) {
	uint8_t regData[6];
	if (HAL_I2C_Mem_Read(dev->i2c, MPU6050_ADDR, 0x3B, 1, &regData, 6, 1000) != HAL_OK) {
		return HAL_ERROR;
	}
	dev->accel[0] = (int16_t)(regData[0] << 8 | regData[1])/16384.0; // Accel X
	dev->accel[1] = (int16_t)(regData[2] << 8 | regData[3])/16384.0; // Accel Y
	dev->accel[2] = (int16_t)(regData[4] << 8 | regData[5])/16384.0; // Accel Z
	return HAL_OK;
}
