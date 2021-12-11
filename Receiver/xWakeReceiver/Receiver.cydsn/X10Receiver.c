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

uint8_t bitNumber = 31;
uint8_t zeroesInRow = 0;
uint32_t received = 0b00000000000000000000000000000000;
uint8_t checkEnvelope();

CY_ISR_PROTO(ISR_ZX_handler);


void initiateReceiver(){
    isr_zx_StartEx(ISR_ZX_handler);
}

uint8_t checkEnvelope(){
    return PIN_ENVELOPE_Read();
}

void setCurrentBit(){
    received |= 1UL << bitNumber;
}

uint8_t parityCheck(uint16_t readCommand){
    if(readCommand & (1 << 6)){
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
    }
}

uint16_t decodeCommand(uint32_t encodedCommand){
    uint8_t decodedCommandBitReached = 15;
    uint16_t decodedCommand = 0b0000000000000000;
    for (int8_t decodingPoint = 27; decodingPoint > 0; decodingPoint -= 2){
        if(encodedCommand & (1 << decodingPoint) && (encodedCommand & (1 << (decodingPoint-1))) == 0){
            decodedCommand |= 1UL << decodedCommandBitReached;
        }
        if((encodedCommand & (1 << (decodingPoint))) == 0 && (encodedCommand & (1 << (decodingPoint-1))) == 0){ 
            return decodedCommand;  //if 2 zeroes were sent together, command end must be reached
        }
        decodedCommandBitReached -= 1;
    }
    return decodedCommand;
}

CY_ISR(ISR_ZX_handler){
    if(checkEnvelope()){
        setCurrentBit();
        zeroesInRow = 0;
    }
    else{
        zeroesInRow = zeroesInRow + 1;
    }
    
    bitNumber = bitNumber - 1;
    if(bitNumber == 27){  // Check if start code, if not reset received bits.
        if(received & (1 << 31) && received & (1 << 30) && received & (1 << 29) && (received & (1 << 28)) == 0 ){
            //Do nothing, Startcode is legit.
        }
        else{
            bitNumber = 31;
            received = 0b00000000000000000000000000000000;
        }
    }
    if(zeroesInRow == 4){
        uint16_t command = decodeCommand(received);
        if(parityCheck(command)){
            insertCommand(command);     //Only Insert into queue for execution, IF PARITY CHECKS OUT.
        }
        received = 0b00000000000000000000000000000000;
    }
}


/* [] END OF FILE */