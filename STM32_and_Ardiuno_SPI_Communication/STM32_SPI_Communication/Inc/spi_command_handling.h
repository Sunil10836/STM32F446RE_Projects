/*
 * spi_cmd_handling.h
 *
 *  Created on: Nov 14, 2025
 *      Author: Sunil Sutar
 */

#ifndef SPI_COMMAND_HANDLING_H_
#define SPI_COMMAND_HANDLING_H_

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "stm32f446xx.h"

//Command Codes
#define COMMAND_LED_CTRL		0x50
#define COMMAND_SENSOR_READ		0x51
#define COMMAND_LED_READ		0x52
#define COMMAND_PRINT			0x53
#define COMMAND_ID_READ			0x54

#define LED_ON					1
#define LED_OFF					0

//Arduino Analog Pins
#define ANALOG_PIN_0			0
#define ANALOG_PIN_1			1
#define ANALOG_PIN_2			2
#define ANALOG_PIN_3			3
#define ANALOG_PIN_4			4

//Arduino LED
#define LED_PIN					9

//Function Prototype
void Command_LED_Control(void);
void Command_Sensor_Read(void);
void LED_Pin_Read(void);
void Command_Print(void);
void Command_ID_Read(void);
uint8_t SPI_VerifyResponse(uint8_t ackbyte);
void delay(void);

#endif /* SPI_COMMAND_HANDLING_H_ */
