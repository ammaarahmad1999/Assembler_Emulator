#ifndef UTIL_H
#define UTIL_H

#include <bits/stdc++.h>
using namespace std;

class Util{
    public:
        static bool isValidLabel(string label);
        static string trim(string token);
        static string AddPadding(string binary, int length);
};

#endif