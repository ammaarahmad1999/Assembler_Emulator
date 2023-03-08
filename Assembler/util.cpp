#include <bits/stdc++.h>
#include "util.h"
using namespace std;

bool Util::isValidLabel(string label){
    if(label[0]<'a' || label[0]>'z')
		return false;
	for (int i=1; i<label.length(); i++)
	{
		if(label[i]=='_')
			continue;
		if(label[i]<'0' || (label[i]>'9' && label[i]<'a') || label[i]>'z')
			return false;
	}
	return true;
}

string Util::trim(string token)		//function to remove leading and trailing spaces
{
	int start = 0, end = token.length()-1;
	while(token[start]==' ' || token[start]=='\t')
		start++;
	while(token[end]==' ' || token[end]=='\t')
		end--;
	return token.substr(start, end-start+1);
}

string Util::AddPadding(string number, int length){
    string padding(length-number.length(), '0');
    return padding + number;
}