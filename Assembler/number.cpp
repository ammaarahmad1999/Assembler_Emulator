#include <bits/stdc++.h>
#include "number.h"
using namespace std;

bool Number::isBinary(string binary){
    for (char ch : binary)
        if(ch <'0' || ch > '1')
            return false;

    return true;
}

bool Number::isOctal(string octal){
    if(octal[0] != '0')
        return false;
    
    for (char ch : octal)
        if(ch < '0' || ch > '7')
            return false;
    
    return true;
}

bool Number::isHex(string hex){
    if(hex.length() <= 2 || hex[0] != '0' || hex[1] != 'x')
        return false;
    
    for (int i=2; i<hex.length(); i++){
        if((hex[i] < '0' || hex[i] > '9') && (hex[i] < 'A' || hex[i] > 'Z'))
            return false;
    }

    return true;
}

bool Number::isDecimal(string decimal){
    int length = decimal.length();
    if(length == 0)
        return false;
    int index = 0;
    if(decimal[index] == '-' || decimal[index] == '+')
        index++;
    
    if(index == length)
        return false;

    while(index < length){
        if(decimal[index] < '0' || decimal[index] > '9')
            return false;
        index++;
    }

    return true;
}