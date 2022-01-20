#ifndef INCLUDED_CCO_H
#define INCLUDED_CCO_H

//returns true if the argument character belongs to the enlisted cipher characters
bool isCipherCharacter(char c)
{
    int i = (int)c;
    return (i >= 110 && i <= 122) || (i >= 48 && i <= 57) || (i >= 48 && i <= 57) || i == 64 || i == 35 || i == 36;
}

//returns the index of argumented cipher text as per the predefined indices for cipher characters
int getCipherCharacterIndex(char c)
{
    int i = (int)c;
    if (i >= 110 && i <= 122)
        return i - 110;
    else if (i >= 48 && i <= 57)
        return i - 35;
    else if (i == 64)
        return 23;
    else
        return i - 11;
}

//returns the character of argumented index as per the predefined indices for cipher characters
char getCipherCharacterFromIndex(int i)
{
    if (i < 13)
        return i + 110;
    else if (i < 23)
        return i + 35;
    else if (i == 23)
        return 64;
    else
        return i + 11;
}

#endif

//enlisted cipher characters along with their defined indices
//  n-z : 0-12
//  0-9 : 13-22
//  @   : 23
//  #   : 24
//  $   : 25