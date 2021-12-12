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
#ifndef Queue_H
#define Queue_H
    
void insertCommand(uint16_t command);
uint16_t withdrawCommand();
uint8_t commandReady();
    
#endif /* Queue_H */   
/* [] END OF FILE */
