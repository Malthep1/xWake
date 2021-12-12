/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "X10Receiver.h"
#include "Queue.h"
#include "PressurePlate.h"
#include "Curtains.h"
#include "Lights.h"
#include "Speaker.h"

void executeCommand(uint16_t command);
uint8_t extractLightParameter(uint8_t command);
void printInteger(int number);

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_1_Start();
    initiateReceiver();
    initiatePressurePlate();
    initiateLights();
    UART_1_PutString("here we go!\r\n");
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    uint16_t testcommand = 0b1000000000000000;
    insertCommand(testcommand);
    for(;;)
    {
        if(commandReady()){
            executeCommand(withdrawCommand());
        }
        CyDelay(100);
    }
}

CY_ISR(ISR_UART_rx_handler)
{
    uint8_t bytesToRead = UART_1_GetRxBufferSize();
    while (bytesToRead > 0)
    {
        uint8_t byteReceived = UART_1_ReadRxData();
        UART_1_WriteTxData(byteReceived); // echo back
        uint16_t uartCommand = 0b1000000000000000;
        insertCommand(uartCommand);
        UART_1_PutString("UART Read");
        bytesToRead--;
    }
}

void executeCommand(uint16_t command){
    //Execute next command
    
    //Pressure Plate - 11
    if(command & (1 << 15) && command & (1 << 14)){
        if(command & (1 << 13)){
            // Engaged -> Probably just monitor weight every loop, if weight suddenly gone, run an interrupt??? 
            UART_1_PutString("PressurePlate Engaged \r\n");
        }
        else{
            // Disengaged
            UART_1_PutString("PressurePlate Disengaged \r\n");
        }
    }
    
    //Curtains - 10
    else if(command & (1 << 15) && (command & (1 << 14)) == 0){
        if(command & (1 << 13)){
            driveMotor(0); // Roll curtains 50% up
            UART_1_PutString("Curtains Up 50% \r\n");
        }
        else{
            driveMotor(1); // Roll curtains 50% down
            UART_1_PutString("Curtains Down 50% \r\n");
        }
    }
    
    //Speaker - 01
    else if((command & (1 << 15)) == 0 && command & (1 << 14)){
        //Screeech speakers???? UART ??? 
        UART_1_PutString("Speaker Engaged \r\n");
    }
    
    //Lights - 00
    else if((command & (1 << 15)) == 0 && (command & (1 << 14)) == 0){
        if(command & (1 << 13)){
            uint8_t duration = extractLightParameter(command);
            startLights(duration);
            UART_1_PutString("Light will brighten over ");
            printInteger(duration); 
            UART_1_PutString("minutes \r\n");
        }
        else{
            turnOffLights();
            UART_1_PutString("Lights Disengaged\r\n");
        }
    }
}

//12-11-10-9-8-7 are the bits ya need
uint8_t extractLightParameter(uint8_t command){
    uint8_t result = 0;
    if(command & (1 << 12)){    result += 32;   }
    if(command & (1 << 11)){    result += 16;   }
    if(command & (1 << 10)){    result += 8;    }    //Looks a little nasty, better way?    
    if(command & (1 << 9)) {    result += 4;    }    //Maybe bitmask and shift it into LSB and take result?
    if(command & (1 << 8)) {    result += 2;    }
    if(command & (1 << 7)) {    result += 1;    }
    return result;
}

void printInteger(int number)
{
    char outputBuffer[256];
       snprintf(outputBuffer, sizeof(outputBuffer), " %d ", number);  
       UART_1_PutString(outputBuffer);
}

/* [] END OF FILE */
