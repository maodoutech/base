#include "strings/string_printf.h"
#include <iostream>
#include <string>

int main(int argc, const char *argv[])
{
    std::string str1;
    if (base::string_printf(&str1, "%s_%d_%lu", "hi", 10, 11) != 0) {
        std::cout << "str1=" << str1 << std::endl;
        return -1;
    }
    std::cout << str1  << std::endl;

    if (base::string_appendf(&str1, "_append_%x", 10) != 0) {
        std::cout << "string_appendf fail!" << std::endl;
        return -1;
    }
    std::cout << str1  << std::endl;
    return 0;
}
