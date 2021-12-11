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
#include "stdio.h"
#define CURTAINROATIONLENGTH 50
uint8_t rotationsFromStart = 0;
uint8_t rotations = 0;
uint8_t drivestate = 0;
uint8_t drivedelay = 20;

void togglePin(int pinno);
void resetPins();

void driveMotor(uint8_t direction){
    while(rotations != (CURTAINROATIONLENGTH/2)){
        switch(drivestate){
            case 1: // Wavedrive. Toggles pin -> Delay ->  Toggles next pin, then Toggles first pin off.
            {       // If direction == 1 -> Inverted.
                if(direction == 1){
                    Pin_Motor_b2_Write(1);
                    Pin_Motor_a_Write(0);
                    CyDelay(drivedelay);
                    Pin_Motor_b_Write(1);
                    Pin_Motor_b2_Write(0);
                    CyDelay(drivedelay);
                    Pin_Motor_a2_Write(1);
                    Pin_Motor_b_Write(0);
                    CyDelay(drivedelay);
                    Pin_Motor_a_Write(1);
                    Pin_Motor_a2_Write(0);
                    CyDelay(drivedelay);
                }
                else {
                    if(rotationsFromStart != 0){
                        Pin_Motor_a2_Write(1);
                        Pin_Motor_a_Write(0);
                        CyDelay(drivedelay);
                        Pin_Motor_b_Write(1);
                        Pin_Motor_a2_Write(0);
                        CyDelay(drivedelay);
                        Pin_Motor_b2_Write(1);
                        Pin_Motor_b_Write(0);
                        CyDelay(drivedelay);
                        Pin_Motor_a_Write(1);
                        Pin_Motor_b2_Write(0);
                        CyDelay(drivedelay);
                    }

                }
                rotations = rotations + 1;
            }
            case 2: // Half-Step. Toggles first pin -> Delay -> Toggles 2nd pin -> Delay -> Toggles first pin -> Delay -> Toggles 3rd -> Delay
            { // Implemented toggle here,  think it's slower. If direction == 1 -> Inverted.
                if(direction == 1){
                    togglePin(4);
                    CyDelay(drivedelay);
                    togglePin(1);
                    CyDelay(drivedelay);
                    togglePin(3);
                    CyDelay(drivedelay);
                    togglePin(4);
                    CyDelay(drivedelay);
                    togglePin(2);
                    CyDelay(drivedelay);
                    togglePin(3);
                    CyDelay(drivedelay);
                    togglePin(1);
                    CyDelay(drivedelay);
                    togglePin(2);
                    CyDelay(drivedelay);
                }
                else{
                   if(rotationsFromStart != 0){
                        togglePin(2);
                        CyDelay(drivedelay);
                        togglePin(1);
                        CyDelay(drivedelay);
                        togglePin(3);
                        CyDelay(drivedelay);
                        togglePin(2);
                        CyDelay(drivedelay);
                        togglePin(4);
                        CyDelay(drivedelay);
                        togglePin(3);
                        CyDelay(drivedelay);
                        togglePin(1);
                        CyDelay(drivedelay);
                        togglePin(4);
                        CyDelay(drivedelay);
                    }
                }
                rotations = rotations + 1;
            }
            case 3: // Full-Step(2 phases). Toggles 1st and 2nd pin -> toggles 1st and 3rd pin -> Toggles 2nd and 4th pin. 
            {       // If direction == 1 -> Inverted.
                if(direction == 1){
                    Pin_Motor_a2_Write(0);
                    Pin_Motor_b2_Write(1);
                    CyDelay(drivedelay);
                    Pin_Motor_a_Write(0);
                    Pin_Motor_b_Write(1);
                    CyDelay(drivedelay);
                    Pin_Motor_b2_Write(0);
                    Pin_Motor_a2_Write(1);
                    CyDelay(drivedelay);
                    Pin_Motor_b_Write(0);
                    Pin_Motor_a_Write(1);
                    CyDelay(drivedelay);
                }
                else{
                    if(rotationsFromStart != 0){
                        Pin_Motor_b2_Write(0);
                        Pin_Motor_a2_Write(1);
                        CyDelay(drivedelay);
                        Pin_Motor_a_Write(0);
                        Pin_Motor_b_Write(1);
                        CyDelay(drivedelay);
                        Pin_Motor_a2_Write(0);
                        Pin_Motor_b2_Write(1);
                        CyDelay(drivedelay);
                        Pin_Motor_b_Write(0);
                        Pin_Motor_a_Write(1);
                        CyDelay(drivedelay);
                    }
                }
                rotations = rotations + 1;
            }
        }
    }
    rotations = 0; 
}
void togglePin(int pinno){ 
    switch(pinno){
        case 1: {
            Pin_Motor_a_Write(~ Pin_Motor_a_Read()); 
        }
        case 2: {
            Pin_Motor_a2_Write(~ Pin_Motor_a2_Read()); 
        }
        case 3: {
            Pin_Motor_b_Write(~ Pin_Motor_b_Read());
        }
        case 4: {
            Pin_Motor_b2_Write(~ Pin_Motor_b2_Read()); 
        }
    }
}

void resetPins(){
    Pin_Motor_a_Write(0); 
    Pin_Motor_a2_Write(0); 
    Pin_Motor_b_Write(0); 
    Pin_Motor_b2_Write(0); 
}

/* [] END OF FILE */
