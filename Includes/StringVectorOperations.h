#ifndef INCLUDED_SVO_H
#define INCLUDED_SVO_H

#include <bits/stdc++.h>

using namespace std;

//returns true if argumented string belongs to the argumented vector of string
bool findStringVector(vector<string> vec, string str)
{
    for (auto it : vec)
        if (it == str)
            return true;
    return false;
}

#endif