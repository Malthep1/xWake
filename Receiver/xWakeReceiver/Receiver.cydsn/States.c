/* ========================================

*/
#include "States.h"


// *********************  IMPORTANT! **********************
//
// Positions of ints in the following matrixes are assigned via the following formula:
// Rows = Motor Position
// Columns = Outputs ordered :  {A, B, A_, B_} where the underscore signifies a complement value.


uint8 INITIAL_POSITION[4]= {0, 0, 0, 0};

uint8 WAVE_DRIVE_FORWARDS[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
};

uint8 WAVE_DRIVE_BACKWARDS[4][4] = {
    {0, 0, 0, 1},
    {0, 0, 1, 0},
    {0, 1, 0, 0},
    {1, 0, 0, 0}
};

uint8 FULL_STEP_FORWARDS[4][4] = {
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 1},
    {1, 0, 0, 1}
};

uint8 FULL_STEP_BACKWARDS[4][4] = {
    {1, 0, 0, 1},
    {0, 0, 1, 1},
    {0, 1, 1, 0},
    {1, 1, 0, 0}
};

uint8 HALF_STEP_FORWARDS[8][4] = {
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 0},
};

uint8 HALF_STEP_BACKWARDS[8][4] = {
    {1, 0, 0, 0},
    {1, 0, 0, 1},
    {0, 0, 0, 1},
    {0, 0, 1, 1},
    {0, 0, 1, 0},
    {0, 1, 1, 0},
    {0, 1, 0, 0},
    {1, 1, 0, 0},  
};


/* [] END OF FILE */
