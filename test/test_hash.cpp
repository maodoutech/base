#include "common/hash.h"

int main(int argc, const char *argv[])
{
    std::string data = "12345";
    fprintf(stdout, "Hash is %lu\n", base::Hash(data)); 
    return 0;
}
