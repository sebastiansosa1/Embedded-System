// File:   game.c
// Author: Joe Mu 89107098
//         Sebastian Sosa 78555646
// Date:   12 Oct 2021
// Descr:  Main implementation for the game SHOOTING PLATES

#include <stdio.h>
#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "display.h"
#include "button.h"
#include "led.h"
#include "target.h"
#include "scope.h"

/* Timing. */
#define PACER_RATE 2000 //Hz
#define TINYGL_RATE 1500 //Hz
#define MESSAGE_RATE 100
#define LED_N_LOOP_CYCLES 50
#define TARGET_TIMEOUT 500
/* Set TARGET_TIMEOUT to:
  400 for difficult
  500 for medium
  600 for easy */

/* Function to display a welcome message. */
void welcome_msg(void)
{
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text(" SHOOTING PLATES ");
}

/* Function to display the Game Over message. */
void end_msg(uint8_t scope_score, uint8_t scope_attempts)
{
    char end_msg_text[100];
    sprintf(end_msg_text, " GAME OVER - SCORE: %d / %d ", scope_score, scope_attempts); 

    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text(end_msg_text);
}

/* Initializes the game. */
void game_init(uint8_t* scope_score, uint8_t* scope_attempts, uint16_t count)
{
    display_clear();
    scope_init();
    *scope_score = 0;
    *scope_attempts = 0;
    target_update(count);
}


int main (void)
{
    uint8_t display_start_msg = 1;
    uint8_t display_end_msg = 0;
    uint8_t play_game = 0;
    uint8_t scope_score = 0;
    uint8_t scope_attempts = 0;
    uint8_t scope_max_attempts = 10;
    uint16_t count = 0;

    pacer_init (PACER_RATE);
    tinygl_init (TINYGL_RATE);   
    button_init ();
    welcome_msg();

    /* Main Loop of the game */
    while (1) {
        /* Turns blue led on while shooting. */
        led_loop_count++;
        if (led_loop_count > LED_N_LOOP_CYCLES)
            led_set(LED1, 0);
        /* Displays the starts message. */
        if (display_start_msg) {
            pacer_wait();
            tinygl_update();
            button_update();
            if (button_push_event_p (0)) {
                display_start_msg = 0;
                play_game = 1;
                game_init(&scope_score, &scope_attempts, count);
            }
        }
        /* While the game is being played. */
        if (play_game) {
            if (scope_attempts > scope_max_attempts) {
                play_game = 0;
                display_end_msg = 1;
                scope_attempts--;
                end_msg(scope_score, scope_attempts);
            } else {
                pacer_wait ();
                display_update ();
                target_display();
                if (count > TARGET_TIMEOUT) {
                    target_off();
                    target_update(count);
                    scope_attempts++;
                    count = 0;
                }
                scope_update(&count, count, &scope_score, &scope_attempts);
            }
        }
        /* Displays the Game Over Message */
        if (display_end_msg) {
            pacer_wait();
            tinygl_update();
            button_update();
            if (button_push_event_p (0)) {
                display_end_msg = 0;
                display_start_msg = 1;
                 welcome_msg();
                display_clear();
            }
        }
        count++;
    }
}

