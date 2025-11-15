# SPI Communication Between STM32 and Arduino UNO

1. This project demonstrates **SPI communication** between the **STM32F446RE (Nucleo-64)** with an **Arduino UNO**.
2. The **STM32F446RE** is configured as **SPI Master** using **bare metal(register-level) programming**, and the **Arduino UNO** is configured as **SPI Slave**
3. **SPI Master(STM32)** and **SPI Slave(Arduino UNO)**  **Command & Response** based communication .
4. When the button on the master is pressed, master sends a command to the slave and slave responds as per the command implementation. 

##  Hardware Used
1. **STM32 Nucleo-F446RE** as **SPI Master**
2. **Arduino UNO** as **SPI Slave**
3. **Logic Level Convertor** : Bidirectional convertor which shifts 3.3 V to 5V and 5V to 3.3V 
4. **USB Logic Anaylyzer**
5. Jumper wires  
6. USB cables

##  Software Used

1. **STM32 Cube IDE**
2. **Ardiuno IDE**
3. **Saleae USB logic analyzer software**

## **SPI Configuration**
1. **STM32F446RE NUCLEO** Configured as **SPI Master**
2. **Ardiuno UNO** Configured as **SPI Slave**

## **STM32F46RE SPI Configuration**
1.  **STM32F46RE** will be in **SPI master mode**
2.  **SPI** is configured in **Full duplex mode**
3.  DFF(Data Frame Format) = 0 i.e. **8-bit Data Format**
4.  **Hardware slave management (SSM = 0)**
5.  SCLK speed = 2MHz , fclk = 16MHz

## **Ardiuno UNO SPI Configuration**
1. **Ardiuno UNO** is configured in **SPI Slave mode**

## Connection Diagram 
<img width="1317" height="695" alt="image" src="https://github.com/user-attachments/assets/2668246d-8878-4440-8514-69f8c7739bd8" />


## **STM32F46RE Code Implementation**
The Code is Implemented using **Bare Metal (register-level) Programming.

**1. STM32F66RE MCU Header file is written.**
   1. GPIO and SPI Peripheral Base Addresses.
   2. GPIO and SPI Peripheral Clock Enable and Disable Macros
   3. GPIO and SPI Register Definition Structure

**3. GPIO and SPI Driver Development**
   1. GPIO and SPI Config Structure
   2. GPIO and SPI Handle Structure
     
**3. APIs Implemented for SPI:**
   1. void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
   2. void SPI_Init(SPI_Handle_t *pSPIHandle);
   3. void SPI_DeInit(SPI_RegDef_t *pSPIx);
   4. void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
   5. void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);
   6. uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName);
   7. void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
   8. void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
   9. void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
       
**4. APIs Implemented for GPIO:**
   1. void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);
   2. void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
   3. void GPIO_DeInit(GPIO_RegDef_t *pGPIO);
   4. uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
   5. uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
   6. void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
   7. void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
   8. void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

**5. Commands Implemented:**

   When the button on the master is pressed, master sends a command to the slave and slave responds as per the command implementation. 
   1. CMD_LED_CTRL   <pin no(1)>     <value(1)>
   2. CMD_SENOSR_READ   <analog pin number(1) >
   3. CMD_LED_READ   <pin no(1) >
   4. CMD_PRINT   <len(2)>  <message(len) >
   5. CMD_ID_READ
   
## How to Run

**STM32**
1. Open STM32CubeIDE
2. Import project
3. Build → Flash

**Arduino UNO**
1. Open Arduino IDE
2. Upload the provided sketch
3. Open Serial Monitor (9600 baud)

