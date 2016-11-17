#include "strings/find_cstr.h"
#include <map>

int main(int argc, const char *argv[])
{
    std::map<std::string, int> string_map;
    string_map["wordid"] = 100;

    std::map<std::string, int>::iterator iter = base::find_cstr(string_map, "wordid");
    if (iter != string_map.end()) {
        fprintf(stdout, "wordid=%d\n", iter->second);
    }
    return 0;
}
