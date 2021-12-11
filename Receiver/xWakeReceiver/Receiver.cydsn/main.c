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

void executeCommand(uint8_t command);

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_1_Start();
    initiateReceiver();
    initiatePressurePlate();
    initiateLights();
    UART_1_PutString("here we go!");
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

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
        //Do something with byte received? 
        bytesToRead--;
    }
}

void executeCommand(uint8_t command){
    //Execute next command
    
    //Pressure Plate - 11
    if(command & (1 << 15) && command & (1 << 14)){
        if(command & (1 << 5)){
            // Engaged -> Probably just monitor weight every loop, if weight suddenly gone, run an interrupt??? 
        }
        else{
            // Disengaged
        }
    }
    
    //Curtains - 10
    if(command & (1 << 15) && (command & (1 << 14)) == 0){
        if(command & (1 << 13)){
            driveMotor(1); // Roll curtains 50% up
        }
        else{
            driveMotor(0); // Roll curtains 50% down
        }
    }
    
    //Speaker - 01
    if((command & (1 << 15)) == 0 && command & (1 << 15)){
        //Screeech speakers???? UART ??? 
    }
    
    //Lights - 00
    if((command & (1 << 15)) == 0 && (command & (1 << 14)) == 0){
        if(command & (1 << 13)){
            //12-11-10-9-8-7 are the bits ya need
        }
        else{
            turnOffLights();
        }
    }
}

/* [] END OF FILE */
