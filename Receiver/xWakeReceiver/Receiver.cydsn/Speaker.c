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
CY_ISR_PROTO(ISR_SPEAKER_handler);

uint8 alternator = 1;
uint8 timesRun = 0;

void initiateSpeaker(){
    isr_speaker_StartEx(ISR_SPEAKER_handler);
    isr_speaker_Disable();
    Timer_4_Start();
    Timer_4_Sleep();
}

void startSpeaker(){
    Timer_4_Wakeup();
    isr_speaker_Enable();
}

CY_ISR(ISR_SPEAKER_handler){
    //Timer_1_ReadStatusRegister();
    UART_1_PutString("SpeakerINTERRUPT\r\n");
    if(timesRun < 6){
        if(alternator){
            Pin_Speaker_Write(1);
            alternator = 0;
        }
        else{
            Pin_Speaker_Write(0);
            alternator = 1;
        }
        timesRun++;
        Timer_4_STATUS;
    }
    else{
        Timer_4_Sleep();
        isr_speaker_Disable();
        Pin_Speaker_Write(0);
        timesRun = 0;
        UART_1_PutString("Speaker has stopped\r\n");
    }
}


/* [] END OF FILE */
