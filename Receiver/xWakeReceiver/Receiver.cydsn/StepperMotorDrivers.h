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
#include "cytypes.h"
#include "States.h"


// These functions control the main driving algorithm
void drive();
uint8* chooseOutputSetup(void);
void rotateMotor(uint8 position, uint8* outputSetup);
void setNextMotorPosition();

// These functions change the way the motor rotates
void decreaseSpeed(void);
void increaseSpeed(void);
void driveForwards(void);
void driveBackwards(void);
void stop(void);
void oneStepForward(void);
void oneStepBackward(void);
void changeDriveMode(void);

/* [] END OF FILE */
