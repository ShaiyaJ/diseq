#ifndef H_DISEQ
#define H_DISEQ

// =====----- DISEQ constants -----===== //
typedef enum {
    NONE
} DSKey;


// =====----- DISEQ functions -----===== //

// Setting up and tearing down the library
void ds_init();                                     // Initialises library state - overrides ctrl-c
void ds_deinit();                                   // Deinitialises library state - removes override for ctrl-c

// Displaying to the terminal
void ds_execute(char* string);                      // Displays a single string immediately to the terminal
void ds_executes(...);                              // Displays a set of strings immediately to the terminal

void ds_queue(char* string);                        // Queues a single string into a buffer to be displayed later
void ds_queues(...);                                // Queues a set of strings immediately to a buffer to be displayed later
void ds_display();                                  // Flushes the buffer that ds_queue() and ds_queues() pushed into

// Getting information about the terminal
void ds_get_cursor_pos(int* row, int* col);         // Returns the current cursor position
void ds_get_terminal_size(int* rows, int* cols);    // Returns the current terminal size

// Manipulating terminal state
void ds_toggle_raw_mode();                          // Toggles the "raw mode" of the terminal

// Getting input from the user
DSKey ds_raw_input();                               // Returns a single character without blocking - can return nothing



// =====----- DISEQ libc impl -----===== //
#ifdef DISEQ_IMPLEMENTATION
// ------------------------------------- //

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void ds_init() {
    // TODO: override signal
}

void ds_deinit() {
    // TODO: un-override signal
}

void ds_execute(char* string) {
    printf("%s", string);
}

void ds_executes(...) {
}

void ds_queue(char* string) {
    static char* queue = NULL;
}

void ds_queues(...) {
}

void ds_display() {
}

void ds_get_cursor_pos(int* row, int* col) {
}

void ds_get_terminal_size(int* rows, int* cols) {
}


// TODO: windows impl
//#ifdef _WIN32
//    void ds_toggle_raw_mode() {
//
//    }
//
//    DSKey ds_raw_input() {
//    }
//#else 
    void ds_toggle_raw_mode() {

    }

    DSKey ds_raw_input() {
    }
//#endif 

// ------------------------------------- //
#endif
// =====---------------------------===== //



#endif
