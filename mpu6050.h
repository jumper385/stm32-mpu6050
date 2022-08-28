/*
 * mpu6050.h
 *
 *  Created on: 20 Aug. 2022
 *      Author: henry
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#include "stm32f1xx_hal.h"

#define MPU6050_ADDR 0x68 << 1

typedef struct {
	I2C_HandleTypeDef *i2c; // i2c handle
	float accel[3]; // [0]:x, [1]:y, [2]:z
	float gyro[3]; // [0]:x, [1]:y, [2]:z
	float temp;
}MPU6050;

/*
 * INITIALIZATION
 * @breif Initializes the MPU6050 by configuring the struct and writing to specific registers
 */
HAL_StatusTypeDef MPU6050_Init(MPU6050 *dev, I2C_HandleTypeDef * i2c);

/*
 * DATA ACQUISITION
 * @brief gets accel, gyro and temp data from the IMU. accel and gyro takes readings from X Y and Z axis
 */
HAL_StatusTypeDef MPU6050_GetAccel(MPU6050 *dev);
HAL_StatusTypeDef MPU6050_GetGyro(MPU6050 *dev);
HAL_StatusTypeDef MPU6050_GetTemp(MPU6050 *dev);

#endif /* INC_MPU6050_H_ */
