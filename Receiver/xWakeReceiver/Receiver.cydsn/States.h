/* ========================================

 * ========================================
*/
#include "cytypes.h"

// header guard : use to avoid redefining enum types across other files
#ifndef STATES_H
#define STATES_H


typedef enum MOTOR_POSITION
{
// Drive Modes WAVE_DRIVE and FULL_STEP only use the first four. HALF_STEP uses all of them. 
    A, B, C, D, E, F, G, H,
}MOTOR_POSITION;

typedef enum MOTOR_DIRECTION
{
    FORWARDS,
    BACKWARDS,
    STOP
}MOTOR_DIRECTION;


typedef enum DRIVE_MODE
{
    WAVE_DRIVE,
    FULL_STEP,
    HALF_STEP
}DRIVE_MODE;

#endif

/* [] END OF FILE */
