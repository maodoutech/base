#include "strings/string_piece.h"
#include <string>

int main(int argc, const char *argv[])
{
    std::string data = " biword plsa";
    base::StringPiece str(data);
    printf("StringPiece data=%s size=%d\n", str.data(), str.size());

    base::StringPiece::value_type value = str[1];
    printf("value=%c\n", value);

    str.trim_spaces();
    printf("StringPiece data=%s size=%d\n", str.data(), str.size());

    std::string prefix = "biword";
    printf("%s start with %s is %d\n", str.data(), prefix.c_str(), str.starts_with(prefix));
    return 0;
}
