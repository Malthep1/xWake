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
#include "stdio.h"
#include "project.h"
#include "Queue.h"

uint8_t bitNumber = 29;
uint8_t zeroesInRow = 0;
uint32_t received = 0b00000000000000000000000000000000;
uint8_t checkEnvelope();
uint8_t startCodeReceived = 0;
uint8_t onesInRow = 0;

CY_ISR_PROTO(ISR_ZX_handler);


void initiateReceiver(){
    isr_zx_StartEx(ISR_ZX_handler);
}

uint8_t checkEnvelope(){
    return PIN_ENVELOPE_Read();
    //return ~PIN_ENVELOPE_Read();
}

void setCurrentBit(){
    received |= 1UL << bitNumber;
}

uint8_t parityCheck(uint16_t readCommand){
    return 1;
    /*if(readCommand & (1 << 6)){
        if(readCommand % 2){
            
            return 0;
        }
        return 1;
    }
    else{
        if(readCommand % 2){
            return 1;
        }
        return 0;
    }*/
}

uint16_t decodeCommand(uint32_t encodedCommand){
    uint8_t decodedCommandBitReached = 15;
    uint16_t decodedCommand = 0b0000000000000000;
    for (int8_t decodingPoint = 27; decodingPoint > 0; decodingPoint -= 2){
        if(encodedCommand & (1 << decodingPoint) && (encodedCommand & (1 << (decodingPoint-1))) == 0){
            decodedCommand |= 1UL << decodedCommandBitReached;
            UART_1_PutString("d1");
        }
        else
            UART_1_PutString("d0");
        if((encodedCommand & (1 << (decodingPoint))) == 0 && (encodedCommand & (1 << (decodingPoint-1))) == 0){ 
            return decodedCommand;  //if 2 zeroes were sent together, command end must be reached
        }
        decodedCommandBitReached -= 1;
    }
    return decodedCommand;
}

CY_ISR(ISR_ZX_handler){
    //UART_1_PutString("Crossing");
    if(checkEnvelope()){
        UART_1_PutString("1");
        setCurrentBit();
        zeroesInRow = 0;
        onesInRow += 1;
    }
    else{
        UART_1_PutString("0");
        zeroesInRow = zeroesInRow + 1;
        onesInRow = 0;
    }
    if(onesInRow == 3){
        startCodeReceived = 1;
        received = 0b11100000000000000000000000000000;
    }
    /*if(bitNumber == 27){  // Check if start code, if not reset received bits.
        if(received & (1 << 31) && received & (1 << 30) && received & (1 << 29) && (received & (1 << 28)) == 0 ){
            //Do nothing, Startcode is legit.
            UART_1_PutString("StartCode Ok\r\n");
            startCodeReceived = 1;
             //received = 0b11100000000000000000000000000000;
        }
        else{
            bitNumber = 31;
            UART_1_PutString("Not startCode\r\n");
            received = 0b00000000000000000000000000000000;
        }
    }*/
    if(startCodeReceived == 1)
    {
        bitNumber = bitNumber - 1;
        if(zeroesInRow == 4){
        //UART_1_PutString("4 o's");
        isr_zx_Disable();
        char buff[40];
        snprintf(buff, sizeof(buff), "reic = %d", received);
        UART_1_PutString(buff);
        uint16_t command = decodeCommand(received);
        if(parityCheck(command)){
            UART_1_PutString("Command Inserted \r\n");   
            startCodeReceived = 0;
            insertCommand(command);     //Only Insert into queue for execution, IF PARITY CHECKS OUT.
            snprintf(buff, sizeof(buff), "cmd = %d", command);
        UART_1_PutString(buff);
        }
        bitNumber = 29;
        received = 0b00000000000000000000000000000000;
        isr_zx_Enable();
        }
    }
    
}


/* [] END OF FILE */
