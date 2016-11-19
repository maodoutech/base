#include <strings/string_splitter.h>
#include <stdio.h>
#include <string>

int main(int argc, const char *argv[])
{
    std::string str = "hello	world	!";
    for (base::StringSplitter s(str.c_str(), '\t'); s; s++) {
        printf("%d %s\n", s.length(), s.field());
    }
    return 0;
}
