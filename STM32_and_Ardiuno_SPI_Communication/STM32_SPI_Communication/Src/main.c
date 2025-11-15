/*
 * main.c
 *
 *  Created on: Nov 15, 2025
 *      Author: Sunil Sutar
 */

#include <stdio.h>
#include <string.h>
#include "stm32f446xx.h"
#include "main.h"

int main()
{
	printf("Application is Running\n");

	GPIO_Button_Init();

	//Configure GPIO Pins to behave as SPI Pins Alt Fun Mode
	SPI2_GPIOInit();

	SPI2_Init();

	printf("SPI Initialization completed\n");

	/*
	 * Making SSOE=1 does NSS Output Enable
	 * NSS pin is automatically managed by hardware
	 * i/e when SPE=1, NSS will be pulled to LOW
	 * and NSS pin will be HIGH when SPE=0
	 */
	SPI_SSOEConfig(SPI2, ENABLE);

	while(1)
	{
		//Wait until Button is Pressed
 		while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_13));
		delay();
		printf("Button Pressed-1\n");

		//Enable SPI2 Peripheral
		SPI_PeripheralControl(SPI2, ENABLE);

		//1. CMD_LED_CTRL <pin no(1)> <Value(1)>
		Command_LED_Control();

		//wait till button is pressed
		while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_13));
		//button de-bouncing delay
		delay();
		printf("Button Pressed-2\n");

		//2. CMD_SENSOR_READ  <analog pin no(1)>
		Command_Sensor_Read();

		//wait till button is pressed
		while(GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_13) );
		//button de-bouncing delay
		delay();
		printf("Button Pressed-3\n");

		//3.  CMD_LED_READ 	 <pin no(1)>
		LED_Pin_Read();

		//wait till button is pressed
		while(GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_13) );
		//button de-bouncing delay
		delay();
		printf("Button Pressed-4\n");

		//4. CMD_PRINT <len(2)> <message(len) >
		Command_Print();

		//wait till button is pressed
		while(GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_13) );
		//button de-bouncing delay
		delay();
		printf("Button Pressed-5\n");

		//5. CMD_ID_READ
		Command_ID_Read();

		//lets confirm SPI is not Busy
		while( SPI_GetFlagStatus(SPI2, SPI_FLAG_BSY));

		//Disable SPI2 Peripheral
		SPI_PeripheralControl(SPI2, DISABLE);
	}
}
