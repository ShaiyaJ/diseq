#ifndef H_DISEQ
#define H_DISEQ

// =====----- DISEQ util functions -----===== //

// Utilities for locally-scoped (stack allocated) sprintf to allow automatic memory cleanup
#define format(buf, fmt, ...)  sprintf(buf, fmt, __VA_ARGS__) ? buf : buf
#define formatn(n, fmt, ...)   format( (char[n]){0}, fmt, __VA_ARGS__ )

// =====----- DISEQ constants and types -----===== //
typedef enum {
    SUCCESS,
    FAILURE
} DSResult;

typedef enum {
    NONE
} DSKey;

typedef struct {
    DSKey key;
    bool ctrl;
    bool alt;
    bool shift;
} DSKeyPress;

// Useful ansi constants
#define DI_ANSI_ESC         "\033["
#define DI_RESET            DI_ANSI_ESC "0m"

// Cursor commands
#define DI_QUERY_CUR_POS    DI_ANSI_ESC "6n"
#define DI_SHOWCUR          DI_ANSI_ESC "?25l"
#define DI_HIDECUR          DI_ANSI_ESC "?25h"

//#define DI_SET_CUR_POS(r, c)        DI_ANSI_ESC #r ";" #c "H"
#define DI_SET_CUR_POS(r, c)        formatn(10, DI_ANSI_ESC "%d;%dH", r, c)
#define DI_MOVE_CUR_UP(n)           DI_ANSI_ESC #n "A"
#define DI_MOVE_CUR_DOWN(n)         DI_ANSI_ESC #n "B"
#define DI_MOVE_CUR_FORWARD(n)      DI_ANSI_ESC #n "C"
#define DI_MOVE_CUR_BACKWARD(n)     DI_ANSI_ESC #n "D"
#define DI_MOVE_CUR_NEXT_LINE(n)    DI_ANSI_ESC #n "E"
#define DI_MOVE_CUR_PREV_LINE(n)    DI_ANSI_ESC #n "F"
#define DI_MOVE_CUR_HORIZONTAL(n)   DI_ANSI_ESC #n "G"

// Console commands
#define SEQD_CLEAR                  DI_ANSI_ESC "2J"

#define DI_SCROLL_UP(n)             DI_ANSI_ESC #n "S"
#define DI_SCROLL_DOWN(n)           DI_ANSI_ESC #n "T"

#define DI_ERASE_DISPLAY(n)         DI_ANSI_ESC #n "J"
#define DI_ERASE_LINE(n)            DI_ANSI_ESC #n "K"
// TODO: could have these in alphabetical order?

// Text styles
#define DI_BOLD                   DI_ANSI_ESC "1m"
#define DI_FAINT                  DI_ANSI_ESC "2m"
#define DI_ITALIC                 DI_ANSI_ESC "3m"
#define DI_UNDERLINE              DI_ANSI_ESC "4m"
#define DI_BLINK_SLOW             DI_ANSI_ESC "5m"
#define DI_BLINK_FAST             DI_ANSI_ESC "6m"
#define DI_REVERSE                DI_ANSI_ESC "7m"
#define DI_CONCEAL                DI_ANSI_ESC "8m"
#define DI_CROSSED_OUT            DI_ANSI_ESC "9m"

#define DI_RESET_BOLD             DI_ANSI_ESC "22m"
#define DI_RESET_ITALIC           DI_ANSI_ESC "23m"
#define DI_RESET_UNDERLINE        DI_ANSI_ESC "24m"
#define DI_RESET_BLINK            DI_ANSI_ESC "25m"
#define DI_RESET_REVERSE          DI_ANSI_ESC "27m"
#define DI_RESET_CONCEAL          DI_ANSI_ESC "28m"
#define DI_RESET_CROSSED_OUT      DI_ANSI_ESC "29m"

// Colour constants
#define DI_FG_BLACK               DI_ANSI_ESC "30m"
#define DI_FG_RED                 DI_ANSI_ESC "31m"
#define DI_FG_GREEN               DI_ANSI_ESC "32m"
#define DI_FG_YELLOW              DI_ANSI_ESC "33m"
#define DI_FG_BLUE                DI_ANSI_ESC "34m"
#define DI_FG_MAGENTA             DI_ANSI_ESC "35m"
#define DI_FG_CYAN                DI_ANSI_ESC "36m"
#define DI_FG_WHITE               DI_ANSI_ESC "37m"

#define DI_FG_BRIGHT_BLACK        DI_ANSI_ESC "90m"
#define DI_FG_BRIGHT_RED          DI_ANSI_ESC "91m"
#define DI_FG_BRIGHT_GREEN        DI_ANSI_ESC "92m"
#define DI_FG_BRIGHT_YELLOW       DI_ANSI_ESC "93m"
#define DI_FG_BRIGHT_BLUE         DI_ANSI_ESC "94m"
#define DI_FG_BRIGHT_MAGENTA      DI_ANSI_ESC "95m"
#define DI_FG_BRIGHT_CYAN         DI_ANSI_ESC "96m"
#define DI_FG_BRIGHT_WHITE        DI_ANSI_ESC "97m"

#define DI_BG_BLACK               DI_ANSI_ESC "40m"
#define DI_BG_RED                 DI_ANSI_ESC "41m"
#define DI_BG_GREEN               DI_ANSI_ESC "42m"
#define DI_BG_YELLOW              DI_ANSI_ESC "43m"
#define DI_BG_BLUE                DI_ANSI_ESC "44m"
#define DI_BG_MAGENTA             DI_ANSI_ESC "45m"
#define DI_BG_CYAN                DI_ANSI_ESC "46m"
#define DI_BG_WHITE               DI_ANSI_ESC "47m"

#define DI_BG_BRIGHT_BLACK        DI_ANSI_ESC "100m"
#define DI_BG_BRIGHT_RED          DI_ANSI_ESC "101m"
#define DI_BG_BRIGHT_GREEN        DI_ANSI_ESC "102m"
#define DI_BG_BRIGHT_YELLOW       DI_ANSI_ESC "103m"
#define DI_BG_BRIGHT_BLUE         DI_ANSI_ESC "104m"
#define DI_BG_BRIGHT_MAGENTA      DI_ANSI_ESC "105m"
#define DI_BG_BRIGHT_CYAN         DI_ANSI_ESC "106m"
#define DI_BG_BRIGHT_WHITE        DI_ANSI_ESC "107m"

// Keys 
// TODO


// =====----- DISEQ functions -----===== //
// Setting up and tearing down the library
//void ds_init();                                     // Initialises library state
//void ds_deinit();                                   // Deinitialises library state

// Displaying to the terminal
void ds_execute(                        // Displays a single string immediately to the terminal
    char* string                        /* Input string */
);

void ds_executes(                       // Displays a set of strings immediately to the terminal
    char* fst,                          /* First input string */
    ...                                 /* Subsequent input string(s) */
);


DSResult ds_queue(                      // Queues a single string into a buffer to be displayed later
    char* string                        /* Input string */
);

DSResult ds_queues(                     // Queues a set of strings immediately to a buffer to be displayed later
    char* fst,                          /* First input string */
    ...                                 /* Subsequent input string(s) */
);

void ds_display();                      // Flushes the buffer that ds_queue() and ds_queues() pushed into


// Getting information about the terminal
DSResult dsr_get_cursor_pos(            // Returns the current cursor position (requires raw mode)
    int* row,                           /* Out parameter to the rows */
    int* col                            /* Out parameter to the columns */
);

DSResult dsr_get_terminal_size(         // Returns the current terminal size (requires raw mode)
    int* row,                           /* Out parameter to the rows */
    int* col                            /* Out parameter to the columns */
);

// Manipulating terminal state
DSResult ds_toggle_raw_mode();          // Toggles the "raw mode" of the terminal

// Getting input from the user
DSKeyPress dsr_raw_input();             // Returns a single character without blocking - can return nothing


// =====----- DISEQ libc impl -----===== //
#ifdef DISEQ_IMPLEMENTATION
// ------------------------------------- //

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    // TODO: windows impl
#else 
    #include <termios.h>
    #include <unistd.h>
    #include <ctype.h>
#endif

// Library setup and teardown + utils //

//void ds_init() {}
//void ds_deinit() {}


// Immediate printing // 

void ds_execute(char* string) {
    fputs(string, stdout);
    fflush(stdout);
    // TODO: free dynamically allocated string
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

static struct {
    char* data;
    int size;
    int capacity;
} queue = {NULL, 0, 0};

DSResult ds_queue(char* string) {
    // Reallocate memory if appending string takes more than capacity
    int string_size = strlen(string);

    if ( (queue.size + string_size) >= queue.capacity ) {
        if (queue.capacity == 0)
            queue.capacity = DI_QUEUE_INIT_CAPACITY;

        char* new_queue = realloc(queue.data, queue.capacity * DI_QUEUE_GROWTH_FACTOR);
        
        if (new_queue == NULL)
            return FAILURE; 

        queue.data = new_queue;
        queue.capacity *= DI_QUEUE_GROWTH_FACTOR;

        return ds_queue(string);   // Retry with new factor
    }

    // Concat string
    strcat(queue.data, string);
    queue.size += string_size;

    return SUCCESS;
}

#define ds_queues(...) _ds_queues(__VA_ARGS__, NULL)
DSResult _ds_queues(char* fst, ...) {
    va_list args;

    va_start(args, fst);

    char* current_arg = fst;
    DSResult current_res;

    do {
        current_res = ds_queue(current_arg);

        // Error handling
        if (current_res == FAILURE)
            return FAILURE;

        current_arg = va_arg(args, char*);
    } while(current_arg != NULL); 

    va_end(args);

    return SUCCESS;
}

void ds_display() {
    fputs(queue.data, stdout);

    free(queue.data);
    queue.data = NULL;

    queue.size = 0;
    queue.capacity = 0;
}



// Terminal state and raw mode functions //

DSResult dsr_get_cursor_pos(int* row, int* col) {
    // Scan for position
    fputs(DI_QUERY_CUR_POS, stdout);
    fflush(stdout);

    int s = scanf("\033[%d;%dR", row, col);

    // Error handling
    if (s == EOF)
        return FAILURE;
    return SUCCESS;
}

DSResult dsr_get_terminal_size(int* rows, int* cols) {
    DSResult res;

    // Get the original position to restore after
    int original_rpos = 0;
    int original_cpos = 0;

    res = dsr_get_cursor_pos(&original_rpos, &original_cpos);

    // Error handling
    if (res == FAILURE)
        goto error;

    // Set the cursor to 999, 999 and read the value
    ds_execute(DI_SET_CUR_POS(999, 999));
    res = dsr_get_cursor_pos(rows, cols);

    // Error handling
    if (res == FAILURE)
        goto error;

    // Restore the old position
    DI_SET_CUR_POS(original_rpos, original_cpos);

    return SUCCESS;

    error:
        return FAILURE;
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
    DSResult ds_toggle_raw_mode() {
        static struct termios raw_term = {0};
        static struct termios cooked_term = {0};

        static bool is_cooked = true;           // By default this is true
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

        if (!is_cooked) {
            if (tcsetattr(STDIN_FILENO, TCSANOW, &cooked_term) < 0)
                goto error;
        } else {
            if (tcsetattr(STDIN_FILENO, TCSANOW, &raw_term) < 0)
                goto error;
        }

        is_cooked = !is_cooked;

        return SUCCESS;

        error:
            return FAILURE;
    }

    DSKeyPress dsr_raw_input() {
        // Read first character
        int fst = getchar();

        if (fst == EOF) 
            goto error;

        // Switch case for control characters
        DSKeyPress press = (DSKeyPress) {NONE, false, false, false};

        switch (fst) {
            // TODO
            default:
                press.key = (DSKey) fst;
                press.shift = isupper(fst);
                
                break;
        }

        // Return final press
        return press;

        error:
            return (DSKeyPress) {NONE, false, false, false};
    }
//#endif 

// ------------------------------------- //
#endif
// =====---------------------------===== //



#endif
