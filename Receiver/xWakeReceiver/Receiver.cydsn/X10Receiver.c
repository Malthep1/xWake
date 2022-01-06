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
    //return PIN_ENVELOPE_Read();
    return PIN_ENVELOPE_Read();
}

void setCurrentBit(){
    received |= 1UL << bitNumber;
}

uint8_t parityCheck(uint16_t readCommand){
    UART_1_PutString("parity:");
    uint8_t ones = 0;
    for (uint8_t i = 16; i > 0; i--)
    {
        if(readCommand & (1 << (i-1))){
            ones++;
        }
    }
    if(ones % 2){ // if there is something left it is not an even number of ones: Something is wrong.
        UART_1_PutString("error");
        return 0;
    }
    else{ //if there is nothing left after %2 then the number is even and parity is true.
        UART_1_PutString("fine");
        return 1;
    }
}

uint16_t decodeCommand(uint32_t encodedCommand){
    if((encodedCommand & 0b000011111111111111111111) == 0)
    {
        //return 1;
    }
    UART_1_PutString("\r\n");
    UART_1_PutString("d");
    uint8_t decodedCommandBitReached = 15;
    uint16_t decodedCommand = 0b0000000000000000;
    for (int8_t decodingPoint = 27; decodingPoint > (bitNumber+4); decodingPoint -= 2){
        if(encodedCommand & (1 << decodingPoint) && (encodedCommand & (1 << (decodingPoint-1))) == 0){
            decodedCommand |= 1UL << decodedCommandBitReached;
            UART_1_PutString("1");
        }
        else if((encodedCommand & (1 << (decodingPoint))) == 0 && encodedCommand & (1 << (decodingPoint-1))){
            UART_1_PutString("0");
        }
        else if((encodedCommand & (1 << (decodingPoint))) == 0 && (encodedCommand & (1 << (decodingPoint-1))) == 0){ 
            return decodedCommand;  //if 2 zeroes were sent together, command end must be reached
        }
        //UART_1_PutString("loop+1");
        decodedCommandBitReached -= 1;
    }
    UART_1_PutString("d\r\n");
    return decodedCommand;
}

CY_ISR(ISR_ZX_handler){
    //UART_1_PutString("Crossing");
    if(checkEnvelope() == 0){
        UART_1_PutString("1");
        if(startCodeReceived == 1){
            setCurrentBit();
        }
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
        UART_1_PutString("three 1's");
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
        if(received & (1 << 28)){
            UART_1_PutString("Starcode Error \r\n");
        }
        else{
            //UART_1_PutString("Startcode valid");
            bitNumber = bitNumber - 1;
            if(zeroesInRow == 4){
                //UART_1_PutString("4 o's");
                isr_zx_Disable();

                uint16_t command = decodeCommand(received);
                if(parityCheck(command)){
                    if(command == 0b1111111111111111 || command == 1){
                        UART_1_PutString("Protocol Error \r\n");
                    }
                    else{
                        UART_1_PutString("Command Inserted \r\n"); 
                        insertCommand(command);
                    }
                    startCodeReceived = 0;
                    bitNumber = 29;
                    received = 0b00000000000000000000000000000000;
                }
                isr_zx_Enable();
            }
        }
    }
    Timer_2_STATUS;
}


/* [] END OF FILE */
