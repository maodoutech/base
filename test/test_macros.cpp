#include "macros.h"
#include <iostream>

using namespace std;

class TestClass {
public:
    TestClass() {}
private:
    DISALLOW_COPY(TestClass);
};

GLOBAL_INIT() {
    int x = 10;
    cout << "xx:" << x << endl;
}

int main(int argc, const char *argv[])
{
    cout << "Hi macros!" << endl;   
    TestClass class1;
    //TestClass class2 = class1;
    
    int CONCAT(a,b) = 10;
    cout << ab << endl;

    int array[] = {0, 1, 2};
    cout << arraysize(array) << endl;

    const int x1 = 10;
    long x2 = base::implicit_cast<long>(x1);
    cout << x2 << endl;

    CASSERT(true, xxxxxxxxxxxxxxxxxxxxxxxx);

    base::ignore_result(x1);

    string string1 = SYMBOLSTR(abc);
    cout << string1 << endl;
    return 0;
}
