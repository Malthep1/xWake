/* ========================================

 * ========================================
*/
#include "StepperMotorDrivers.h"
#include "project.h"
#include "States.h"

// Define Globals
MOTOR_POSITION currentMotorPosition = A;
DRIVE_MODE driveMode = WAVE_DRIVE;
MOTOR_DIRECTION motorDirection = STOP;

// Output pin setup matrixes
extern uint8 WAVE_DRIVE_FORWARDS[][4];
extern uint8 WAVE_DRIVE_BACKWARDS[][4];
extern uint8 FULL_STEP_FORWARDS[][4];
extern uint8 FULL_STEP_BACKWARDS[][4];
extern uint8 HALF_STEP_FORWARDS[][4];
extern uint8 HALF_STEP_BACKWARDS[][4];
extern uint8 INITIAL_POSITION[4];


void drive()
{
    rotateMotor((int)currentMotorPosition, chooseOutputSetup());
    setNextMotorPosition();
}

uint8* chooseOutputSetup()
{
    // Returns a pointer to the correct output setup matrix
    switch (driveMode)
    {
        case WAVE_DRIVE:
        {
            if (motorDirection == FORWARDS)
            {
                return (uint8*)WAVE_DRIVE_FORWARDS;
            }
            else if (motorDirection == BACKWARDS)
            {
                return (uint8*)WAVE_DRIVE_BACKWARDS;
            }
            else
            {
                return (uint8*)INITIAL_POSITION;
            }
        }break;
        
        case FULL_STEP:
        {
            if (motorDirection == FORWARDS)
            {
                return *FULL_STEP_FORWARDS;
            }
            else if (motorDirection == BACKWARDS)
            {
                return *FULL_STEP_BACKWARDS;
            }
            else
                return (uint8*)INITIAL_POSITION;
        }break;
        
        case HALF_STEP:
        {
            if (motorDirection == FORWARDS)
            {
                return *HALF_STEP_FORWARDS;
            }
            else if (motorDirection == BACKWARDS)
            {
                return *HALF_STEP_BACKWARDS;
            }
            else
                return (uint8*)INITIAL_POSITION;
        }break;
    }
}

void rotateMotor(uint8 position, uint8* outputSetup)
{
    // Use s_x variables for debugging
    uint8 s1 = outputSetup[0 + position * 4];
    uint8 s2 = outputSetup[1 + position * 4];
    uint8 s3 = outputSetup[2 + position * 4];
    uint8 s4 = outputSetup[3 + position * 4];
    // Set debug here
    Pin_Motor_a_Write(s1);
    Pin_Motor_b_Write(s2);
    Pin_Motor_a2_Write(s3);
    Pin_Motor_b2_Write(s4);
}

void setNextMotorPosition()
{
    // Cycles to the next motor position. 8 positions for a half step mode, 4 for the rest
    switch (driveMode){
        case HALF_STEP:
        {
            if (currentMotorPosition == H)
                  currentMotorPosition = A;
            else
                currentMotorPosition++;
        }break;
        
        default:
        {
            if (currentMotorPosition == D)
                currentMotorPosition = A;
            else
                currentMotorPosition++;
        }break;
    }
}

void changeDriveMode()
{
    switch (driveMode)
    {
        case WAVE_DRIVE:
        {
            UART_1_PutString("Changing Drive Mode : Full Step\r\n");
            driveMode = FULL_STEP;
        }break;
        
        case FULL_STEP:
        {
            UART_1_PutString("Changing Drive Mode : Half Step\r\n");
            driveMode = HALF_STEP;
        }break;
        
        case HALF_STEP:
        {
            UART_1_PutString("Changing Drive Mode : Wave Drive\r\n");
            driveMode = WAVE_DRIVE;
        }break;
    }
}

// These functions change the speed of motor rotation

void increaseSpeed()
{
    // Read the current period register of the timer. If not at the mimimum (50000), reduce it
    // Reducing the period register makes the period of the timer interrupts shorter, increasing
    // Motor speed
    int period = Timer_1_ReadPeriod();
    if (period > 50000)
    {
        UART_1_PutString("Increasing speed\r\n");
        Timer_1_WritePeriod(period - 1000);
    }
    else
        UART_1_PutString("Error: Speed already at maximum!\r\n");
}

void decreaseSpeed()
{
    // Read the current period register of the timer. If not at the maximum (100000), increase it
    // Increasing the period register makes the period of the timer interrupts longer, decreasing
    // Motor speed
    int period = Timer_1_ReadPeriod();
    if (period < 100000)
    {
        UART_1_PutString("Decreasing speed\r\n");
        Timer_1_WritePeriod(period + 1000);
       
    }
    else
        UART_1_PutString("Error: Speed already at minimum!\r\n");
}

// Direction changes via setting motorDirection enum to the appropriate value
// Reset current motor position on direction change

void driveForwards()
{
    UART_1_PutString("Set direction: forwards\r\n");
    currentMotorPosition = A;
    motorDirection = FORWARDS;
}

void driveBackwards()
{
    UART_1_PutString("Set direction: backwards\r\n");
    currentMotorPosition = A;
    motorDirection = BACKWARDS;
}

void stop()
{
    UART_1_PutString("Stop\r\n");
    motorDirection = STOP;
    currentMotorPosition = A;
}

void oneStepForward()
{
    if (motorDirection == STOP)
    {
        UART_1_PutString("Rotating one step forward \r\n");
        motorDirection = FORWARDS;
        drive();
        motorDirection = STOP;
    }
    else
        UART_1_PutString("To rotate one step, stop the motor ('0') first\r\n");
    
}

void oneStepBackward()
{
    
    if (motorDirection == STOP)
    {
        UART_1_PutString("Rotating one step backward \r\n");
        motorDirection = BACKWARDS;
        drive();
        motorDirection = STOP;
    }
    else
        UART_1_PutString("To rotate one step, stop the motor ('0') first\r\n");
}


/* [] END OF FILE */
