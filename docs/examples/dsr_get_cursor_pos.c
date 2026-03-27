#define DISEQ_IMPLEMENTATION
#include "../../diseq.h"
#include <stdio.h>

int main(void) {
    int row = 0;
    int col = 0;

    if (ds_toggle_raw_mode() == FAILURE)
        printf("Failed to set raw mode!\n");

    dsr_get_cursor_pos(&row, &col);

    printf("%d, %d", row, col);

    if (ds_toggle_raw_mode() == FAILURE)
        printf("Failed to set raw mode!\n");

    return 0;
}
