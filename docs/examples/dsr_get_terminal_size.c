#define DISEQ_IMPLEMENTATION
#include "../../diseq.h"
#include <stdio.h>

int main(void) {
    int rows = 0;
    int cols = 0;

    if (ds_toggle_raw_mode() == FAILURE)
        printf("Failed to set raw mode!\n");

    dsr_get_terminal_size(&rows, &cols);

    printf("%d, %d", rows, cols);

    if (ds_toggle_raw_mode() == FAILURE)
        printf("Failed to set raw mode!\n");

    return 0;
}
