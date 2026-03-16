#ifndef H_DISEQ
#define H_DISEQ

// =====----- DISEQ constants -----===== //
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

#define DI_ANSI_ESC "\033["

#define DI_QUERY_CUR_POS DI_ANSI_ESC "6n"
#define DI_SET_CUR_POS(r, c)                        // Implementation left to library author


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

    /*
    // Read escape output from stdin 
    char* line = NULL;
    size_t size = 0;

    getdelim(&line, &size, 'R', stdin); 
    line[size] = '\0';

    // Get position info and store in out param
    int s = sscanf(line, "\033[%d;%dR", row, col);
    free(line);
    */
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
    DI_SET_CUR_POS(999, 999);
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
