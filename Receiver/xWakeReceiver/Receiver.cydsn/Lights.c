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

CY_ISR_PROTO(ISR_LIGHT_TIMER_handler);

uint8 timer = 0;
uint8 brigteningDuration = 0;

void initiateLights(){
    isr_light_timer_StartEx(ISR_LIGHT_TIMER_handler);
    PWM_1_Start();
    PWM_1_WriteCompare(0);
    Timer_1_Start();
}

void startLights(uint8_t duration){
    timer = duration;
    brigteningDuration = duration;
}

void turnOffLights(){
    PWM_1_WriteCompare(0);
}

CY_ISR(ISR_LIGHT_TIMER_handler){
    Timer_1_ReadStatusRegister();
    if(timer){
        timer -= 1;
        PWM_1_WriteCompare(((70/brigteningDuration) * (brigteningDuration - timer)) + 2.33);
        if(timer == 0){
            PWM_1_WriteCompare(100);
        }
    }
    UART_1_PutString("LightTimer Interrupt \r\n");
}

/* [] END OF FILE */
