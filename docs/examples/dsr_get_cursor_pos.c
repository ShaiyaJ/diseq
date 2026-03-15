#define DISEQ_IMPLEMENTATION
#include "../../diseq.h"
#include <stdio.h>

int main(void) {
    int row = 0;
    int col = 0;

    ds_toggle_raw_mode();
    dsr_get_cursor_pos(&row, &col);

    printf("%d, %d", row, col);

    ds_toggle_raw_mode();

    return 0;
}
