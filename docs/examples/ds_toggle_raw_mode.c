#define DISEQ_IMPLEMENTATION
#include "../../diseq.h"

int main(void) {
    // Setting up raw mode - this operation can fail in some terminals
    if (ds_toggle_raw_mode() == FAILURE)
        goto failure;

    // Reading characters until q is pressed
    char c;
    while ((c = getchar()) != 'q')
        printf("Input wasn't q, it was: %c\n", c);

    // Exiting raw mode
    if (ds_toggle_raw_mode() == FAILURE)
        goto failure;

    return 0;

failure:
    printf("Failed to set raw mode!\n");
    return 1;
}
