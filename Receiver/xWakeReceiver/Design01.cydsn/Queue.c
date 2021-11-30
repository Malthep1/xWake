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

#define columns 3
#define rows 256

/* 
    Queue is a two-dimensional array holding with each row holding a command in the form of {device, command, parameter}.
*/
int queue[rows][columns];

uint8_t frontPoint = -1;
uint8_t rearPoint = -1;

void insertCommand(uint8_t device, uint8_t command, uint8_t parameter){
    if(rearPoint == rows - 1){
        //queue full, error handle.
    }
    else{
        if(frontPoint == -1){
            frontPoint = 0;
        }
        rearPoint = rearPoint + 1;
        queue[rearPoint][0] = device;
        queue[rearPoint][1] = command;
        queue[rearPoint][2] = parameter;
        
    }
}
uint8_t * withdrawCommand(){
    if(frontPoint == -1 || frontPoint > rearPoint ){
        frontPoint = -1;
        rearPoint = -1;
    }
    static uint8_t command[3];
    
    command[0] = queue[frontPoint][0];
    command[1] = queue[frontPoint][1];
    command[2] = queue[frontPoint][2];
    
    return command;
}

/* [] END OF FILE */
