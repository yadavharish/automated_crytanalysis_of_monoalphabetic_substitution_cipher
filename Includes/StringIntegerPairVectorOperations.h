#ifndef INCLUDED_SIPMO_H
#define INCLUDED_SIPMO_H

#include <bits/stdc++.h>

using namespace std;

//returns true if first argumented pair's second element is greater than second argumented pair's second element
//used for sorting the vector of pair of string and integer based on the second element in non-increasing order
bool sIPairVectorValCmp(pair<string, int> &a, pair<string, int> &b)
{
    return a.second > b.second;
}

//returns the iterator to pair of string and integer in the argumented vector having first element equal to argument key
vector<pair<string, int>>::iterator findSIPairVector(vector<pair<string, int>>::iterator begin, vector<pair<string, int>>::iterator end, string key)
{
    vector<pair<string, int>>::iterator it = begin;
    for (; it != end; ++it)
        if (it->first == key)
            return it;
    return it;
}

#endif