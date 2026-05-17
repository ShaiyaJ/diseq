#define DISEQ_IMPLEMENTATION
#include "../../diseq.h"

int main(void) {
    ds_toggle_raw_mode();

    char c;

    while ((c = dsr_raw_input().key) != 'q')
        printf("Input wasn't q, it was: %c\n", c);

    ds_toggle_raw_mode();

    return 0;
}
