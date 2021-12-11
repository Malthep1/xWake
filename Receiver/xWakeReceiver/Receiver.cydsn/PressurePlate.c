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
CY_ISR_PROTO(ISR_PRESSURE_PLATE_handler);

uint8_t pressurePlateEngaged = 0;

void initiatePressurePlate(){
    isr_pressure_plate_StartEx(ISR_PRESSURE_PLATE_handler);    
}

CY_ISR(ISR_PRESSURE_PLATE_handler){
    pressurePlateEngaged = 1;
}
//Copy code from GFV4 if plausible solution. This interrupt is prolly not gonna work -.-'''

/* [] END OF FILE */
