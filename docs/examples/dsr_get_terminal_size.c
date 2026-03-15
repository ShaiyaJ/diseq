#define DISEQ_IMPLEMENTATION
#include "../../diseq.h"
#include <stdio.h>

int main(void) {
    int rows = 0;
    int cols = 0;

    ds_toggle_raw_mode();
    dsr_get_terminal_size(&rows, &cols);

    printf("%d, %d", rows, cols);

    return 0;
}
