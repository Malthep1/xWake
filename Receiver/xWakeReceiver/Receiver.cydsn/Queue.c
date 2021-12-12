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
#define queueSize 10

/* 
    Queue is a two-dimensional array holding with each row holding a command in the form of {device, command, parameter}.
*/
uint16_t queue[queueSize];

uint8_t frontPoint = 0;
uint8_t rearPoint = 0;
uint8_t queueState = 0;

void insertCommand(uint16_t command){
    if(rearPoint == queueSize - 1){
        // Full queue, command will be discarded.
    }
    else{
        if(rearPoint == 0){
            queueState = 1;
        }
        queue[rearPoint] = command;
        rearPoint = rearPoint + 1;
    }
}
uint16_t withdrawCommand(){
  uint16_t temp = queue[frontPoint];
  frontPoint = frontPoint + 1;
  if(frontPoint == rearPoint ){
    frontPoint = 0;
    rearPoint = 0;
    queueState = 0;
  }
  return temp;
}

uint8_t commandReady(){
    return queueState;
}

/* [] END OF FILE */
