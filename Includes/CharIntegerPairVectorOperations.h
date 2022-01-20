#ifndef INCLUDED_CIPVO_H
#define INCLUDED_CIPVO_H

#include <bits/stdc++.h>

using namespace std;

//returns true if first argumented pair's second element is greater than second argumented pair's second element
//used for sorting the vector of pair of char and integer based on the second element in non-increasing order
bool cIPairVectorValCmp(pair<char, int> &a, pair<char, int> &b)
{
    return a.second > b.second;
}

//returns the iterator to pair of char and integer in the argumented vector having first element equal to argument key
vector<pair<char, int>>::iterator findCIPairVector(vector<pair<char, int>>::iterator begin, vector<pair<char, int>>::iterator end, char key)
{
    vector<pair<char, int>>::iterator it = begin;
    for (; it != end; ++it)
        if (it->first == key)
            return it;
    return it;
}

#endif