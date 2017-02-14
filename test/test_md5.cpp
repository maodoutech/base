#include "md5.h"
#include <iostream>

using namespace std;

int main(int argc, const char *argv[])
{
    base::MD5Context context = "abc1233123123123";
    base::MD5Init(&context);

    base::MD5Digest digest;
    base::MD5Final(&digest, &context);

    cout << base::MD5DigestToBase16(digest) << endl;
    return 0;
}
