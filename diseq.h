#ifndef H_DISEQ
#define H_DISEQ

// =====----- DISEQ util functions -----===== //

// Utilities for locally-scoped (stack allocated) sprintf to allow automatic memory cleanup
#define di_format(buf, fmt, ...)            /* implementation left to library implementor */
#define di_formatn(n, fmt, ...)             di_format((char[n]){0}, fmt, __VA_ARGS__ )

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
#define DS_ANSI_ESC         "\033["
#define DS_RESET            DS_ANSI_ESC "0m"

// Cursor commands
#define DS_QUERY_CUR_POS    DS_ANSI_ESC "6n"
#define DS_SHOWCUR          DS_ANSI_ESC "?25l"
#define DS_HIDECUR          DS_ANSI_ESC "?25h"

//#define DS_SET_CUR_POS(r, c)        DS_ANSI_ESC #r ";" #c "H"
#define DS_SET_CUR_POS(r, c)        di_formatn(10, DS_ANSI_ESC "%d;%dH", r, c)
#define DS_MOVE_CUR_UP(n)           DS_ANSI_ESC #n "A"
#define DS_MOVE_CUR_DOWN(n)         DS_ANSI_ESC #n "B"
#define DS_MOVE_CUR_FORWARD(n)      DS_ANSI_ESC #n "C"
#define DS_MOVE_CUR_BACKWARD(n)     DS_ANSI_ESC #n "D"
#define DS_MOVE_CUR_NEXT_LINE(n)    DS_ANSI_ESC #n "E"
#define DS_MOVE_CUR_PREV_LINE(n)    DS_ANSI_ESC #n "F"
#define DS_MOVE_CUR_HORIZONTAL(n)   DS_ANSI_ESC #n "G"

// Console commands
#define DS_CLEAR                    DS_ANSI_ESC "2J"

#define DS_SCROLL_UP(n)             DS_ANSI_ESC #n "S"
#define DS_SCROLL_DOWN(n)           DS_ANSI_ESC #n "T"

#define DS_ERASE_DISPLAY(n)         DS_ANSI_ESC #n "J"
#define DS_ERASE_LINE(n)            DS_ANSI_ESC #n "K"
// TODO: could have these in alphabetical order?

// Text styles
#define DS_BOLD                   DS_ANSI_ESC "1m"
#define DS_FAINT                  DS_ANSI_ESC "2m"
#define DS_ITALIC                 DS_ANSI_ESC "3m"
#define DS_UNDERLINE              DS_ANSI_ESC "4m"
#define DS_BLINK_SLOW             DS_ANSI_ESC "5m"
#define DS_BLINK_FAST             DS_ANSI_ESC "6m"
#define DS_REVERSE                DS_ANSI_ESC "7m"
#define DS_CONCEAL                DS_ANSI_ESC "8m"
#define DS_CROSSED_OUT            DS_ANSI_ESC "9m"

#define DS_RESET_BOLD             DS_ANSI_ESC "22m"
#define DS_RESET_ITALIC           DS_ANSI_ESC "23m"
#define DS_RESET_UNDERLINE        DS_ANSI_ESC "24m"
#define DS_RESET_BLINK            DS_ANSI_ESC "25m"
#define DS_RESET_REVERSE          DS_ANSI_ESC "27m"
#define DS_RESET_CONCEAL          DS_ANSI_ESC "28m"
#define DS_RESET_CROSSED_OUT      DS_ANSI_ESC "29m"

// Colour constants
#define DS_FG_BLACK               DS_ANSI_ESC "30m"
#define DS_FG_RED                 DS_ANSI_ESC "31m"
#define DS_FG_GREEN               DS_ANSI_ESC "32m"
#define DS_FG_YELLOW              DS_ANSI_ESC "33m"
#define DS_FG_BLUE                DS_ANSI_ESC "34m"
#define DS_FG_MAGENTA             DS_ANSI_ESC "35m"
#define DS_FG_CYAN                DS_ANSI_ESC "36m"
#define DS_FG_WHITE               DS_ANSI_ESC "37m"

#define DS_FG_BRIGHT_BLACK        DS_ANSI_ESC "90m"
#define DS_FG_BRIGHT_RED          DS_ANSI_ESC "91m"
#define DS_FG_BRIGHT_GREEN        DS_ANSI_ESC "92m"
#define DS_FG_BRIGHT_YELLOW       DS_ANSI_ESC "93m"
#define DS_FG_BRIGHT_BLUE         DS_ANSI_ESC "94m"
#define DS_FG_BRIGHT_MAGENTA      DS_ANSI_ESC "95m"
#define DS_FG_BRIGHT_CYAN         DS_ANSI_ESC "96m"
#define DS_FG_BRIGHT_WHITE        DS_ANSI_ESC "97m"

#define DS_BG_BLACK               DS_ANSI_ESC "40m"
#define DS_BG_RED                 DS_ANSI_ESC "41m"
#define DS_BG_GREEN               DS_ANSI_ESC "42m"
#define DS_BG_YELLOW              DS_ANSI_ESC "43m"
#define DS_BG_BLUE                DS_ANSI_ESC "44m"
#define DS_BG_MAGENTA             DS_ANSI_ESC "45m"
#define DS_BG_CYAN                DS_ANSI_ESC "46m"
#define DS_BG_WHITE               DS_ANSI_ESC "47m"

#define DS_BG_BRIGHT_BLACK        DS_ANSI_ESC "100m"
#define DS_BG_BRIGHT_RED          DS_ANSI_ESC "101m"
#define DS_BG_BRIGHT_GREEN        DS_ANSI_ESC "102m"
#define DS_BG_BRIGHT_YELLOW       DS_ANSI_ESC "103m"
#define DS_BG_BRIGHT_BLUE         DS_ANSI_ESC "104m"
#define DS_BG_BRIGHT_MAGENTA      DS_ANSI_ESC "105m"
#define DS_BG_BRIGHT_CYAN         DS_ANSI_ESC "106m"
#define DS_BG_BRIGHT_WHITE        DS_ANSI_ESC "107m"

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

#undef di_format
#define di_format(buf, fmt, ...) _ds_format(buf, fmt, __VA_ARGS__)
char* _ds_format(char* buf, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    vsprintf(buf, fmt, args);

    va_end(args);

    return buf;
}


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
    fputs(DS_QUERY_CUR_POS, stdout);
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
    ds_execute(DS_SET_CUR_POS(999, 999));
    res = dsr_get_cursor_pos(rows, cols);

    // Error handling
    if (res == FAILURE)
        goto error;

    // Restore the old position
    ds_execute( DS_SET_CUR_POS(original_rpos, original_cpos) );

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
