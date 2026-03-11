#define DISEQ_IMPLEMENTATION
#include "../../diseq.h"
#include <stdio.h>

int main(void) {
    int row = 0;
    int col = 0;
    ds_get_cursor_pos(&row, &col);

    printf("%d, %d", row, col);

    return 0;
}
