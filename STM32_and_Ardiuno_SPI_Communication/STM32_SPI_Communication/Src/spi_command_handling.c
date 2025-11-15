/*
 * spi_command_handling.h
 *
 *  Created on: Nov 15, 2025
 *      Author: HP
 */

#include "spi_command_handling.h"

void Command_LED_Control(void)
{
	uint8_t dummy_write = 0xff;
	uint8_t dummy_read;
	uint8_t ackbyte;
	uint8_t args[2];

	//1. CMD_LED_CTRL <pin no(1)> <Value(1)>
	uint8_t command_code = COMMAND_LED_CTRL;

	//send the command
	SPI_SendData(SPI2, &command_code, 1);

	//do dummy read to clear off the RXNE flag
	SPI_ReceiveData(SPI2, &dummy_read, 1);

	//first send some dummy data to fetch the response from the slave
	SPI_SendData(SPI2, &dummy_write, 1);

	//Read the ACK Byte received
	SPI_ReceiveData(SPI2, &ackbyte, 1);

	if(SPI_VerifyResponse(ackbyte))
	{
		//Send Arguments
		args[0] = LED_PIN;
		args[1] = LED_ON;
		SPI_SendData(SPI2, args, 2);
		printf("COMMAND_LED_CTRL Executed\n");
	}

}

void Command_Sensor_Read(void)
{
	//2. CMD_SENSOR_READ	<analog pin no(1)>
	uint8_t dummy_write = 0xff;
	uint8_t dummy_read;
	uint8_t ackbyte;
	uint8_t args;
	uint8_t analog_read;

	//1. CMD_LED_CTRL <pin no(1)> <Value(1)>
	uint8_t command_code = COMMAND_SENSOR_READ;

	//send the command
	SPI_SendData(SPI2, &command_code, 1);

	//do dummy read to clear off the RXNE flag
	SPI_ReceiveData(SPI2, &dummy_read, 1);

	//first send some dummy data to fetch the response from the slave
	SPI_SendData(SPI2, &dummy_write, 1);

	//Read the ACK Byte received
	SPI_ReceiveData(SPI2, &ackbyte, 1);

	if(SPI_VerifyResponse(ackbyte))
	{
		//Send Arguments
		args = ANALOG_PIN_0;
		SPI_SendData(SPI2, &args, 1);

		//do dummy read to clear off the RXNE flag
		SPI_ReceiveData(SPI2, &dummy_read, 1);

		//insert some delay so that slave can ready with data
		delay();

		//first send some dummy data to fetch the response from the slave
		SPI_SendData(SPI2, &dummy_write, 1);

		SPI_ReceiveData(SPI2, &analog_read, 1);
		printf("COMMAND_SENSOR_READ %d\n",analog_read);
	}
}

void LED_Pin_Read(void)
{
	//3.  CMD_LED_READ 	 <pin no(1) >
	uint8_t dummy_write = 0xff;
	uint8_t dummy_read;
	uint8_t ackbyte;
	uint8_t args;
	uint8_t led_status;

	uint8_t command_code = COMMAND_LED_READ;

	//send command
	SPI_SendData(SPI2,&command_code,1);

	//do dummy read to clear off the RXNE
	SPI_ReceiveData(SPI2,&dummy_read,1);

	//Send some dummy byte to fetch the response from the slave
	SPI_SendData(SPI2,&dummy_write,1);

	//read the ack byte received
	SPI_ReceiveData(SPI2,&ackbyte,1);

	if( SPI_VerifyResponse(ackbyte))
	{
		args = LED_PIN;

		//send arguments
		SPI_SendData(SPI2,&args,1); //sending one byte of

		//do dummy read to clear off the RXNE
		SPI_ReceiveData(SPI2,&dummy_read,1);

		//insert some delay so that slave can ready with the data
		delay();

		//Send some dummy bits (1 byte) fetch the response from the slave
		SPI_SendData(SPI2,&dummy_write,1);

		SPI_ReceiveData(SPI2,&led_status,1);
		printf("COMMAND_READ_LED %d\n",led_status);
	}
}

void Command_Print(void)
{
	//4. CMD_PRINT 		<len(2)>  <message(len) >
	uint8_t dummy_write = 0xff;
	uint8_t dummy_read;
	uint8_t ackbyte;
	uint8_t args;

	uint8_t command_code = COMMAND_PRINT;

	//send command
	SPI_SendData(SPI2,&command_code,1);

	//do dummy read to clear off the RXNE
	SPI_ReceiveData(SPI2,&dummy_read,1);

	//Send some dummy byte to fetch the response from the slave
	SPI_SendData(SPI2,&dummy_write,1);

	//read the ack byte received
	SPI_ReceiveData(SPI2,&ackbyte,1);

	uint8_t message[] = "Hello ! How are you ??";
	if( SPI_VerifyResponse(ackbyte))
	{
		args = strlen((char*)message);

		//send arguments
		SPI_SendData(SPI2,&args,1); //sending length

		//do dummy read to clear off the RXNE
		SPI_ReceiveData(SPI2,&dummy_read,1);

		delay();

		//send message
		for(int i = 0 ; i < args ; i++)
		{
			SPI_SendData(SPI2,&message[i],1);
			SPI_ReceiveData(SPI2,&dummy_read,1);
		}
		printf("COMMAND_PRINT Executed \n");
	}
}

void Command_ID_Read(void)
{
	//5. CMD_ID_READ
	uint8_t dummy_write = 0xff;
	uint8_t dummy_read;
	uint8_t ackbyte;
	uint8_t id[11];
	uint32_t i=0;

	uint8_t command_code = COMMAND_ID_READ;

	//send command
	SPI_SendData(SPI2,&command_code,1);

	//do dummy read to clear off the RXNE
	SPI_ReceiveData(SPI2,&dummy_read,1);

	//Send some dummy byte to fetch the response from the slave
	SPI_SendData(SPI2,&dummy_write,1);

	//read the ack byte received
	SPI_ReceiveData(SPI2,&ackbyte,1);

	if( SPI_VerifyResponse(ackbyte))
	{
		//read 10 bytes id from the slave
		for(  i = 0 ; i < 10 ; i++)
		{
			//send dummy byte to fetch data from slave
			SPI_SendData(SPI2,&dummy_write,1);
			SPI_ReceiveData(SPI2,&id[i],1);
		}

		id[10] = '\0';

		printf("COMMAND_ID : %s \n",id);

	}
}

uint8_t SPI_VerifyResponse(uint8_t ackbyte)
{
	if(ackbyte == 0xF5)
	{
		return 1;			//ACK
	}
	return 0;				//NACK
}

void delay(void)
{
	for(uint32_t i=0; i < 500000; i++);
}
