// File:   target.c
// Author: Joe Mu 89107098
//         Sebastian Sosa 78555646
// Date:   12 Oct 2021
// Descr:  This module implements functionalities related to the target.
// Functions descriptions on corresponding header file.

#include "pacer.h"
#include "tinygl.h"
#include "target.h"


// Global variables tinygl_point_t, target_coord assigned in target.h
tinygl_point_t target_coord;


void target_update(uint8_t seed)
{
    tinygl_coord_t tmp = target_coord.x;
    target_coord.x = (seed * target_coord.y + 1) % 5;
    target_coord.y = (seed * tmp + 3) % 7;
}


void target_display()
{
    tinygl_draw_point (target_coord, 1);
}


void target_off()
{
    tinygl_draw_point(target_coord, 0);
}
