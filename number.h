#ifndef NUMBER_H
#define NUMBER_H

#include <bits/stdc++.h>
using namespace std;

class Number{
    public:
        static bool isBinary(string binary);
        static bool isOctal(string octal);
        static bool isHex(string hex);
        static bool isDecimal(string decimal);
};

#endif