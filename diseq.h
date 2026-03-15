#ifndef H_DISEQ
#define H_DISEQ

// =====----- DISEQ constants -----===== //
typedef enum {
    NONE
} DSKey;

#define DI_ANSI_ESC "\033["

#define DI_QUERY_CUR_POS DI_ANSI_ESC "6n"
#define DI_SET_CUR_POS(r, c)                        // Implementation left to library author


// =====----- DISEQ functions -----===== //

// Setting up and tearing down the library
//void ds_init();                                     // Initialises library state
//void ds_deinit();                                   // Deinitialises library state

// Displaying to the terminal
void ds_execute(char* string);                      // Displays a single string immediately to the terminal
void ds_executes(char* fst, ...);                   // Displays a set of strings immediately to the terminal

void ds_queue(char* string);                        // Queues a single string into a buffer to be displayed later
void ds_queues(char* fst, ...);                     // Queues a set of strings immediately to a buffer to be displayed later
void ds_display();                                  // Flushes the buffer that ds_queue() and ds_queues() pushed into

// Getting information about the terminal
void dsr_get_cursor_pos(int* row, int* col);        // Returns the current cursor position (requires raw mode)
void dsr_get_terminal_size(int* rows, int* cols);   // Returns the current terminal size (requires raw mode)

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
#include <termios.h>
#include <unistd.h>

// #define's implementation //
#undef DI_SET_CUR_POS
#define DI_SET_CUR_POS(r, c)    printf(DI_ANSI_ESC "%d;%dH", r, c)

// Library setup and teardown + utils //

//void ds_init() {}
//void ds_deinit() {}


// Immediate printing // 

void ds_execute(char* string) {
    fputs(string, stdout);
    fflush(stdout);
}

#define ds_executes(...) _ds_executes(__VA_ARGS__, NULL)
void _ds_executes(char* fst, ...) {
    va_list args;

    va_start(args, fst);

    char* current_arg = fst;

    do {
        fputs(current_arg, stdout);
        current_arg = va_arg(args, char*);
    } while(current_arg != NULL); 

    va_end(args);
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
    if (string == NULL) {       // TODO: factor out instead of having a special case?
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

#define ds_queues(...) _ds_queues(__VA_ARGS__, NULL)
void _ds_queues(char* fst, ...) {
    va_list args;

    va_start(args, fst);

    char* current_arg = fst;

    do {
        ds_queue(current_arg);
        current_arg = va_arg(args, char*);
    } while(current_arg != NULL); 

    va_end(args);
}

void ds_display() {
    ds_queue(NULL);
}


// Terminal state and raw mode functions //

void dsr_get_cursor_pos(int* row, int* col) {
    fputs(DI_QUERY_CUR_POS, stdout);
    
    // Read escape output from stdin 
    char* line = NULL;
    size_t size = 0;

    getdelim(&line, &size, 'R', stdin); // FIXME: blocking
    line[size] = '\0';

    // Get position info and store in out param
    sscanf(line, "\033[%d;%dR", row, col);
    free(line);

    error:
        return; // TODO: error value?
}

void dsr_get_terminal_size(int* rows, int* cols) {
    // Get the original position to restore after
    int original_rpos = 0;
    int original_cpos = 0;

    dsr_get_cursor_pos(&original_rpos, &original_cpos);

    // Set the cursor to 999, 999 and read the value
    DI_SET_CUR_POS(999, 999);
    dsr_get_cursor_pos(rows, cols);

    // Restore the old position
    DI_SET_CUR_POS(original_rpos, original_cpos);
}

// TODO: implement?
//void ds_get_mouse_pos(int* row, int* col) {
//}


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
        static struct termios raw_term = {0};
        static struct termios cooked_term = {0};

        static bool is_cooked = false;
        static bool terms_initialised = false;

        // Setting terminal defaults if this is the first time running the function
        if (!terms_initialised) {
            // Setting cooked term
            if (tcgetattr(STDIN_FILENO, &cooked_term) < 0)
                goto error;   

            // Setting raw term
            raw_term = cooked_term;

            raw_term.c_lflag &= ~(ICANON | ECHO);

            raw_term.c_cc[VMIN] = 1;
            raw_term.c_cc[VTIME] = 0;

            // Setting flag
            terms_initialised = true;
        }

        // Toggling the terminal mode
        fflush(stdout);

        if (!is_cooked)
            if (tcsetattr(STDIN_FILENO, TCSANOW, &cooked_term) < 0)
                goto error;
        else
            if (tcsetattr(STDIN_FILENO, TCSANOW, &raw_term) < 0)
                goto error;

        is_cooked = !is_cooked;

        error:
            return; // TODO: error value?
    }

    DSKey ds_raw_input() {
        return NONE;
    }
//#endif 

// ------------------------------------- //
#endif
// =====---------------------------===== //



#endif
