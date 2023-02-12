// File:   scope.h
// Author: Joe Mu 89107098
//         Sebastian Sosa 78555646
// Date:   12 Oct 2021
// Descr:  This module implements functionalities related to the gun's scope of the game.

#ifndef SCOPE_H
#define SCOPE_H
#include "tinygl.h"
#include "target.h"

// Four coordinates of the scope:
#define SCOPE_E (tinygl_point_t){scope_center.x+1,scope_center.y}
#define SCOPE_W (tinygl_point_t){scope_center.x-1,scope_center.y}
#define SCOPE_S (tinygl_point_t){scope_center.x,scope_center.y+1}
#define SCOPE_N (tinygl_point_t){scope_center.x,scope_center.y-1}
// Centre of the screen:
#define SCOPE_STARTING_POS (tinygl_point_t){2,3}


extern tinygl_point_t scope_center;
extern uint8_t led_loop_count;


/* Changes the coordinate of the scope based on navswitch input.
   Does NOT update the display, only modifies the global_variable scope_center
   Use scope_update() to update display as well */
void scope_move(void);

/* Displays the scope on the ledmat. */
void scope_display(void);

/* Turns the scope off while its position is being updated. */
void scope_off(void);

/* Initialises the scope to be centered in the ledmat. */
void scope_init(void);

/* Updates and displays the scope at the new coordinate based on the navswitch input */
void scope_update(uint16_t* count, uint8_t seed, uint8_t* scope_score, uint8_t* scope_attempts);

/* Compares the position of the scope to the position of the target and proceed updating 
score variables. */
void scope_shoot(uint16_t* count, uint8_t seed, uint8_t* scope_score, uint8_t* scope_attempts);

#endif /* SCOPE_H */
