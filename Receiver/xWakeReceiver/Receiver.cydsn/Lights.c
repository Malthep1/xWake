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
    isr_light_timer_Disable();
    PWM_1_Start();
    PWM_1_WriteCompare(0);
    Timer_1_Start();
    Timer_1_Sleep();
}

void startLights(uint8_t duration){
    timer = duration;
    char buff[10];
    snprintf(buff, sizeof(buff), "dur: %d", duration);
    UART_1_PutString(buff);
    brigteningDuration = duration;
    Timer_1_Wakeup();
    isr_light_timer_Enable();
}

void turnOffLights(){
    PWM_1_WriteCompare(0);
    Timer_1_Sleep();
    isr_light_timer_Disable();
}

CY_ISR(ISR_LIGHT_TIMER_handler){
    //Timer_1_ReadStatusRegister();
    if(timer){
        timer -= 1;
        PWM_1_WriteCompare(((30/brigteningDuration) * (brigteningDuration - timer)) + 2.33);
        uint8_t pwm = PWM_1_ReadCompare();
        char buff[10];
        snprintf(buff, sizeof(buff), "pwm: %d", pwm);
        UART_1_PutString(buff);
    }
    if(timer == 0){
            PWM_1_WriteCompare(100);
    }
    UART_1_PutString("LightTimer Interrupt \r\n");
    Timer_1_STATUS;
}

/* [] END OF FILE */
