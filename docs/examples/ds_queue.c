#define DISEQ_IMPLEMENTATION
#include "../../diseq.h"

int main(void) {
    ds_queue("Hello, ");
    ds_queue("world");
    ds_queue("!");
    ds_display();

    return 0;
}
