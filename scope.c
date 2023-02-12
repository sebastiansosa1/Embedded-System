// File:   scope.c
// Author: Joe Mu 89107098
//         Sebastian Sosa 78555646
// Date:   12 Oct 2021
// Descr:  This module implements functionalities related to the gun's scope of the game.
// Functions descriptions on corresponding header file.

#include "scope.h"
#include "tinygl.h"
#include "navswitch.h"
#include "display.h"
#include "led.h"


tinygl_point_t scope_center;
uint8_t led_loop_count = 0;

void scope_display()
{
    tinygl_draw_point (SCOPE_N, 1);
    tinygl_draw_point (SCOPE_S, 1);
    tinygl_draw_point (SCOPE_W, 1);
    tinygl_draw_point (SCOPE_E, 1);
}


void scope_off()
{
    tinygl_draw_point (SCOPE_E, 0);
    tinygl_draw_point (SCOPE_S, 0);
    tinygl_draw_point (SCOPE_W, 0);
    tinygl_draw_point (SCOPE_N, 0);
}


void scope_shoot(uint16_t* count, uint8_t seed, uint8_t* scope_score, uint8_t* scope_attempts)
{
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        (*scope_attempts)++;
        led_loop_count = 0;
        led_set(LED1, 1);
        if (scope_center.x == target_coord.x && scope_center.y == target_coord.y) {
            (*scope_score)++;
            target_off();
            target_update(seed);
            *count = 0;
        }
    }
}


void scope_move()
{
    navswitch_update();
    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        scope_center.y--;
    }
    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        scope_center.y++;
    }
    if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        scope_center.x++;
    }
    if (navswitch_push_event_p(NAVSWITCH_WEST)) {
        scope_center.x--;
    }
    // Keeps the scope within the display
    if (scope_center.x < 0)
        scope_center.x = 0;
    if (scope_center.x == LEDMAT_COLS_NUM)
        scope_center.x = LEDMAT_COLS_NUM - 1;
    if (scope_center.y == LEDMAT_ROWS_NUM )
        scope_center.y = LEDMAT_ROWS_NUM - 1;
    if (scope_center.y < 0)
        scope_center.y = 0;
}


void scope_update(uint16_t* count, uint8_t seed, uint8_t* scope_score, uint8_t* scope_attempts)
{
    scope_off();
    scope_move();
    scope_display();
    scope_shoot(count, seed, scope_score, scope_attempts);
}


void scope_init()
{
    scope_center = SCOPE_STARTING_POS;
    scope_display();
}
