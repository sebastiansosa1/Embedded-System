// File:   target.c
// Author: Joe Mu 89107098
//         Sebastian Sosa 78555646
// Date:   12 Oct 2021
// Descr:  This module implements functionalities related to the target.

#ifndef TARGET_H
#define TARGET_H
#include "system.h"
#include "display.h"
#include "tinygl.h"


/* Global variable used to store the position of the target. */
extern tinygl_point_t target_coord;

/* Updates the position of the target to a new pseudo-random position within the display.
   modifies the global variable target_coord does NOT return any value */
void target_update(uint8_t seed);

/* Displays the position of the target */
void target_display (void);

/* Turns the target off to get it ready for a position update. */
void target_off(void);

#endif /* TARGET_H */
