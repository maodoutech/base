#include "strings/bit_array.h"
#include <stdio.h>

void print_bin(uint64_t n);

int main(int argc, const char *argv[])
{
    uint64_t* bit_array = base::bits::bit_array_malloc(20);

    base::bits::bit_array_set(bit_array, 3);
    printf("%x\n", *bit_array);

    base::bits::bit_array_set(bit_array, 0);
    printf("%x\n", *bit_array);

    base::bits::bit_array_unset(bit_array, 3);
    printf("%x\n", *bit_array);

    uint64_t bit = base::bits::bit_array_get(bit_array, 0);
    printf("%d\n", bit);

    return 0;
}
