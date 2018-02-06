#ifndef ERROR_H
#define ERROR_H

#include <string>

using namespace std;

struct Error
{
    int code = 0;
    string message = "";
};

#endif // ERROR_H