#include "strings/bits.h"
#include <stdio.h>

int main(int argc, const char *argv[])
{
    uint32_t x = 5;
    fprintf(stdout, "i=%d\n", base::bits::Log2Floor(x));
    fprintf(stdout, "i=%d\n", base::bits::Log2Ceiling(x));
    return 0;
}
