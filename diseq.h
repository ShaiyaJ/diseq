#ifndef H_DISEQ
#define H_DISEQ

// =====----- DISEQ constants -----===== //
typedef enum {
    NONE
} DSKey;


// =====----- DISEQ functions -----===== //

// Setting up and tearing down the library
//void ds_init();                                     // Initialises library state
//void ds_deinit();                                   // Deinitialises library state

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
#include <string.h>


// Library setup and teardown + utils //

// TODO: check safety
int _w_asprintf(char* strp, const char* fmt, ...) {  // malloc'd sprintf
    va_list args;

    // Get size
    va_start(args, fmt);
    int size = vsprintf(NULL, fmt, args);
    va_end(args);

    // Error checking before allocation
    if (size < 0)
        return -1;

    // Allocate memory
    strp = malloc(size + 1);

    // Error checking allocation
    if (strp == NULL)
        return -1;

    // Call sprintf
    return vsprintf(strp, fmt, args);
}

//void ds_init() {}
//void ds_deinit() {}



// Immediate printing // 

void ds_execute(char* string) {
    fputs(string, stdout);
}

#define ds_executes(...) do { ds_executes(__VA_ARGS__, NULL); } while(0)
void ds_executes(char* fst, ...) {
    va_list args;

    va_start(fst);

    char* current_arg;

    do {
        current_arg = va_arg(args, char*);
        fputs(arg);
    } while(arg != NULL); 

    va_end(fst);
}



// Queuing printing //

#ifndef DI_QUEUE_GROWTH_FACTOR
#define DI_QUEUE_GROWTH_FACTOR 1.5
#endif

#ifndef DI_QUEUE_INIT_CAPACITY
#define DI_QUEUE_INIT_CAPACITY 256
#endif

void ds_queue(char* string) {
    static char* queue = NULL;
    static int size = 0;
    static int capacity = 0;

    // Special case for NULL
    if (string == NULL) {
        fputs(queue, stdout);

        free(queue);
        queue = NULL;

        size = 0;
        capacity = 0;
        return;
    }
    

    // Reallocate memory if appending string takes more than capacity
    int string_size = strlen(string);

    if ( (size + string_size) >= capacity ) {
        if (capacity == 0)
            capacity = DI_QUEUE_INIT_CAPACITY;

        char* new_queue = realloc(queue, capacity * DI_QUEUE_GROWTH_FACTOR);
        
        if (new_queue == NULL)
            return;  // TODO: error value?

        queue = new_queue;
        capacity = capacity * DI_QUEUE_GROWTH_FACTOR;

        ds_queue(string);   // Retry with new factor
        return;
    }

    // Concat string
    strcat(queue, string);
    size += string_size;
}

#define ds_queues(...) do { ds_queues(__VA_ARGS__, NULL); } while(0)
void ds_queues(char* fst, ...) {
    va_list args;

    va_start(fst);

    char* current_arg;

    do {
        current_arg = va_arg(args, char*);
        ds_queue(arg);
    } while(arg != NULL); 

    va_end(fst);
}

void ds_display() {
    ds_queue(NULL);
}



// Terminal info //

void ds_get_cursor_pos(int* row, int* col) {
}

void ds_get_terminal_size(int* rows, int* cols) {
}


// Terminal state and raw mode functions //

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
