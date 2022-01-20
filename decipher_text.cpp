#include <bits/stdc++.h>
#include <fstream>

#include "./Includes/StringIntegerPairVectorOperations.h"
#include "./Includes/CharIntegerPairVectorOperations.h"
#include "./Includes/CipherCharacterOperations.h"
#include "./Includes/StringVectorOperations.h"
#include "./Includes/CommonWordsDictionary.h"

using namespace std;

int main()
{
    //extractedKey's ith character is the substituted cipher text character for ith english characters (0-indexed)
    //reverse's ith character is the plain text (english) character which is substituted by ith cipher text characters (indexing defined in CipherCharacterOperations.h)
    string extractedKey = "**************************", reverseKey = "**************************";
    int substitutionsFound = 0;
    //some variables required for operations
    char c1, c2, c3;
    bool flag;
    int i, j;

    //**************************************************inputting cipher text**************************************************
    string cipherText;
    ifstream fin;
    fin.open("./ciphertext.txt");
    getline(fin, cipherText);
    fin.close();

    //**************************************************calculating frequencies**************************************************
    vector<pair<char, int>> singleLetterFreq, firstLetterFreq, lastLetterFreq, oneLetterWordFreq;
    vector<pair<string, int>> digraphFreq, trigraphFreq, repeatingLetterFreq, twoLettersWordFreq, threeLettersWordFreq, fourLettersWordFreq;
    vector<pair<char, int>>::iterator cIt;
    vector<pair<string, int>>::iterator sIt, sIt2, sIt3;

    for (i = 0; i < cipherText.length(); ++i)
        if (isCipherCharacter(cipherText[i]))
        {
            //counting the frequency of each cipher text character
            cIt = findCIPairVector(singleLetterFreq.begin(), singleLetterFreq.end(), cipherText[i]);
            if (cIt != singleLetterFreq.end())
                cIt->second++;
            else
                singleLetterFreq.push_back({cipherText[i], 1});

            //counting the frequency of first character of each word
            if (i == 0 || !isCipherCharacter(cipherText[i - 1]))
            {
                cIt = findCIPairVector(firstLetterFreq.begin(), firstLetterFreq.end(), cipherText[i]);
                if (cIt != firstLetterFreq.end())
                    cIt->second++;
                else
                    firstLetterFreq.push_back({cipherText[i], 1});
            }

            //counting the frequency of last character of each word
            if (i == cipherText.length() - 1 || !isCipherCharacter(cipherText[i + 1]))
            {
                cIt = findCIPairVector(lastLetterFreq.begin(), lastLetterFreq.end(), cipherText[i]);
                if (cIt != lastLetterFreq.end())
                    cIt->second++;
                else
                    lastLetterFreq.push_back({cipherText[i], 1});
            }

            //counting the frequency of digraphs
            if (i < cipherText.length() - 1 && isCipherCharacter(cipherText[i + 1]))
            {
                sIt = findSIPairVector(digraphFreq.begin(), digraphFreq.end(), cipherText.substr(i, 2));
                if (sIt != digraphFreq.end())
                    sIt->second++;
                else
                    digraphFreq.push_back({cipherText.substr(i, 2), 1});
            }

            //counting the frequency of trigraphs
            if (i < cipherText.length() - 2 && isCipherCharacter(cipherText[i + 1]) && isCipherCharacter(cipherText[i + 2]))
            {
                sIt = findSIPairVector(trigraphFreq.begin(), trigraphFreq.end(), cipherText.substr(i, 3));
                if (sIt != trigraphFreq.end())
                    sIt->second++;
                else
                    trigraphFreq.push_back({cipherText.substr(i, 3), 1});
            }

            //counting the frequency of repeating letters pairs
            if (i < cipherText.length() - 1 && cipherText[i] == cipherText[i + 1])
            {
                sIt = findSIPairVector(repeatingLetterFreq.begin(), repeatingLetterFreq.end(), cipherText.substr(i, 2));
                if (sIt != repeatingLetterFreq.end())
                    sIt->second++;
                else
                    repeatingLetterFreq.push_back({cipherText.substr(i, 2), 1});
            }

            //counting the frequency of one letter words
            if ((i == 0 || !isCipherCharacter(cipherText[i - 1])) && (i == cipherText.length() - 1 || !isCipherCharacter(cipherText[i + 1])))
            {
                cIt = findCIPairVector(oneLetterWordFreq.begin(), oneLetterWordFreq.end(), cipherText[i]);
                if (cIt != oneLetterWordFreq.end())
                    cIt->second++;
                else
                    oneLetterWordFreq.push_back({cipherText[i], 1});
            }

            //counting the frequency of two letter words
            if (i < cipherText.length() - 1 && (i == 0 || !isCipherCharacter(cipherText[i - 1])) && isCipherCharacter(cipherText[i + 1]) && (i == cipherText.length() - 2 || !isCipherCharacter(cipherText[i + 2])))
            {
                sIt = findSIPairVector(twoLettersWordFreq.begin(), twoLettersWordFreq.end(), cipherText.substr(i, 2));
                if (sIt != twoLettersWordFreq.end())
                    sIt->second++;
                else
                    twoLettersWordFreq.push_back({cipherText.substr(i, 2), 1});
            }

            //counting the frequency of three letter words
            if (i < cipherText.length() - 2 && (i == 0 || !isCipherCharacter(cipherText[i - 1])) && isCipherCharacter(cipherText[i + 1]) && isCipherCharacter(cipherText[i + 2]) && (i == cipherText.length() - 3 || !isCipherCharacter(cipherText[i + 3])))
            {
                sIt = findSIPairVector(threeLettersWordFreq.begin(), threeLettersWordFreq.end(), cipherText.substr(i, 3));
                if (sIt != threeLettersWordFreq.end())
                    sIt->second++;
                else
                    threeLettersWordFreq.push_back({cipherText.substr(i, 3), 1});
            }

            //counting the frequency of four letter words
            if (i < cipherText.length() - 3 && (i == 0 || !isCipherCharacter(cipherText[i - 1])) && isCipherCharacter(cipherText[i + 1]) && isCipherCharacter(cipherText[i + 2]) && isCipherCharacter(cipherText[i + 3]) && (i == cipherText.length() - 4 || !isCipherCharacter(cipherText[i + 4])))
            {
                sIt = findSIPairVector(fourLettersWordFreq.begin(), fourLettersWordFreq.end(), cipherText.substr(i, 4));
                if (sIt != fourLettersWordFreq.end())
                    sIt->second++;
                else
                    fourLettersWordFreq.push_back({cipherText.substr(i, 4), 1});
            }
        }

    //sorting all frequencies in non-increasing order
    sort(singleLetterFreq.begin(), singleLetterFreq.end(), cIPairVectorValCmp);
    sort(firstLetterFreq.begin(), firstLetterFreq.end(), cIPairVectorValCmp);
    sort(lastLetterFreq.begin(), lastLetterFreq.end(), cIPairVectorValCmp);
    sort(oneLetterWordFreq.begin(), oneLetterWordFreq.end(), cIPairVectorValCmp);
    sort(digraphFreq.begin(), digraphFreq.end(), sIPairVectorValCmp);
    sort(trigraphFreq.begin(), trigraphFreq.end(), sIPairVectorValCmp);
    sort(repeatingLetterFreq.begin(), repeatingLetterFreq.end(), sIPairVectorValCmp);
    sort(twoLettersWordFreq.begin(), twoLettersWordFreq.end(), sIPairVectorValCmp);
    sort(threeLettersWordFreq.begin(), threeLettersWordFreq.end(), sIPairVectorValCmp);
    sort(fourLettersWordFreq.begin(), fourLettersWordFreq.end(), sIPairVectorValCmp);

    //**************************************************Applying the English Heuristics to find the Substitutions**************************************************

    //finding the number of one letter words in the encrypted text, if one only 1 such word exist, then based on the analysis of English language, we assume it to be letter 'a', and if 2 such word exist then we assign it the more frequent one to be 'a' and other to be 'i'.
    //Note: In English, only 'a' and 'I' are single letter words.
    //checking if there is any single letter word in provided cipher text or not
    if (oneLetterWordFreq.size() > 0)
    {
        cIt = oneLetterWordFreq.begin();
        //substituting most frequent one letter word cipher text character to 'a'
        if (extractedKey[0] == '*' && reverseKey[getCipherCharacterIndex(cIt->first)] == '*')
        {
            extractedKey[0] = cIt->first;
            reverseKey[getCipherCharacterIndex(cIt->first)] = 'a';
            substitutionsFound++;
        }
        //checking if there are more than one single letter word in provided cipher text or not
        if (oneLetterWordFreq.size() == 2)
        {
            cIt++;
            //substituting second most frequent one letter word cipher text character to 'i' if exist
            if (extractedKey[8] == '*' && reverseKey[getCipherCharacterIndex(cIt->first)] == '*')
            {
                extractedKey[8] = cIt->first;
                reverseKey[getCipherCharacterIndex(cIt->first)] = 'i';
                substitutionsFound++;
            }
        }
    }

    //using 'a' as an anchor for 'and' which is one of the most frequent trigraph in English
    //checking if 'a' is substituted to any cipher text character or not
    if (extractedKey[0] != '*')
    {
        flag = false;
        for (sIt = threeLettersWordFreq.begin(); sIt != threeLettersWordFreq.end(); ++sIt)
        {
            //finding most frequent three-letter word in given cipher-text with first cipher character as one substituted for 'a' and second and third characters not being equal, as it would not lead to 'and' rather to 'all' according to heuristics of English language
            if (sIt->first[0] == extractedKey[0] && sIt->first[1] != sIt->first[2])
            {
                for (sIt2 = trigraphFreq.begin(); sIt2 != trigraphFreq.end(); ++sIt2)
                    //for confirmation, just checking whether it is also one of the most frequent trigraph as 'are' is one of the most frequent three-letter word but not most frequent trigraph
                    if (sIt->first == sIt2->first)
                    {
                        //substituting most frequent trigraph's (starting with character substituted for 'a') second cipher character with 'n'
                        if (extractedKey[13] == '*' && reverseKey[getCipherCharacterIndex(sIt->first[1])] == '*')
                        {
                            extractedKey[13] = sIt->first[1];
                            reverseKey[getCipherCharacterIndex(sIt->first[1])] = 'n';
                            substitutionsFound++;
                        }
                        //substituting most frequent trigraph's (starting with character substituted for 'a') third cipher character with 'd'
                        if (extractedKey[3] == '*' && reverseKey[getCipherCharacterIndex(sIt->first[2])] == '*')
                        {
                            extractedKey[3] = sIt->first[2];
                            reverseKey[getCipherCharacterIndex(sIt->first[2])] = 'd';
                            substitutionsFound++;
                        }
                        flag = true;
                        break;
                    }
            }
            if (flag)
                break;
        }
    }

    //using 'a' as an anchor and 'and' if recovered for 'are' which is one of the most frequent three-letter word in English
    //checking if 'a', 'n' and 'd' are substituted to any cipher text character or not
    if (extractedKey[0] != '*' && extractedKey[13] != '*' && extractedKey[3] != '*')
        for (sIt = threeLettersWordFreq.begin(); sIt != threeLettersWordFreq.end(); ++sIt)
            //finding most frequent three-letter word in given cipher-text with first cipher character as one substituted for 'a' and second and third characters not being equal, nor being substituted to 'n' and 'd' respectively
            if (sIt->first[0] == extractedKey[0] && sIt->first[1] != sIt->first[2] && sIt->first[1] != extractedKey[13] && sIt->first[2] != extractedKey[3])
            {
                //substituting most frequent three-letter's (starting with character substituted for 'a' and not ending with 'nd' or double) second cipher character with 'r'
                if (extractedKey[17] == '*' && reverseKey[getCipherCharacterIndex(sIt->first[1])] == '*')
                {
                    extractedKey[17] = sIt->first[1];
                    reverseKey[getCipherCharacterIndex(sIt->first[1])] = 'r';
                    substitutionsFound++;
                }
                //substituting most frequent trigraph's (starting with character substituted for 'a') third cipher character with 'e'
                if (extractedKey[4] == '*' && reverseKey[getCipherCharacterIndex(sIt->first[2])] == '*')
                {
                    extractedKey[4] = sIt->first[2];
                    reverseKey[getCipherCharacterIndex(sIt->first[2])] = 'e';
                    substitutionsFound++;
                }
                break;
            }

    //using 'all' being one of the most frequent three-letter word to find 'l' if 'a' is recovered
    //checking if 'a' is recovered
    if (extractedKey[0] != '*')
        for (sIt = threeLettersWordFreq.begin(); sIt != threeLettersWordFreq.end(); ++sIt)
            if (sIt->first[0] == extractedKey[0] && sIt->first[1] == sIt->first[2])
                //substituting most frequent three-letter word's (with first character substituted for 'a' and same second and third character) second and third cipher character with 'l'
                if (extractedKey[11] == '*' && reverseKey[getCipherCharacterIndex(sIt->first[1])] == '*')
                {
                    extractedKey[11] = sIt->first[1];
                    reverseKey[getCipherCharacterIndex(sIt->first[1])] = 'l';
                    substitutionsFound++;
                    break;
                }

    //using 'that' being one of the most frequent four-letter word to find 't' and 'h' if 'a' is recovered
    flag = false;
    //checking if 'a' is recovered
    if (extractedKey[0] != '*')
        for (sIt = fourLettersWordFreq.begin(); sIt != fourLettersWordFreq.end(); ++sIt)
        {
            if (sIt->first[2] == extractedKey[0] && sIt->first[0] == sIt->first[3])
                //substituting most frequent four-letter word's (with third character substituted for 'a' and same first and last character) first and last cipher character with 't' and second cipher character with 'h'
                if (extractedKey[19] == '*' && reverseKey[getCipherCharacterIndex(sIt->first[0])] == '*' && extractedKey[7] == '*' && reverseKey[getCipherCharacterIndex(sIt->first[1])] == '*')
                {
                    extractedKey[19] = sIt->first[0];
                    reverseKey[getCipherCharacterIndex(sIt->first[0])] = 't';
                    extractedKey[7] = sIt->first[1];
                    reverseKey[getCipherCharacterIndex(sIt->first[1])] = 'h';
                    substitutionsFound += 2;
                    flag = true;
                }
            if (flag)
                break;
        }

    //using 'th', 'the' and 'the' being one of the most frequent bigraph, trigraph and three letter word to find 't', 'h', 'e'.
    flag = false;
    for (sIt = threeLettersWordFreq.begin(); sIt != threeLettersWordFreq.end(); ++sIt)
    {
        c1 = sIt->first[0];
        c2 = sIt->first[1];
        c3 = sIt->first[2];
        //checking if the chosen three-letter word is not 'and' as it also resembles the property along with 'an'
        if (c1 != extractedKey[0] && c2 != extractedKey[13] && c3 != extractedKey[3] && (extractedKey[19] == '*' || extractedKey[19] == c1) && (extractedKey[7] == '*' || extractedKey[7] == c2))
        {
            for (sIt2 = trigraphFreq.begin(); sIt2 != trigraphFreq.end(); ++sIt2)
            {
                if (sIt->first == sIt2->first)
                {
                    for (sIt3 = digraphFreq.begin(); sIt3 != digraphFreq.end(); ++sIt3)
                    {
                        if (c1 == sIt3->first[0] && c2 == sIt3->first[1])
                        {
                            //substituting most frequent bigraph, trigraph, three-letter word's first cipher character with 't'
                            if (extractedKey[19] == '*' && reverseKey[getCipherCharacterIndex(c1)] == '*')
                            {
                                extractedKey[19] = c1;
                                reverseKey[getCipherCharacterIndex(c1)] = 't';
                                substitutionsFound++;
                                flag = true;
                            }
                            //substituting most frequent bigraph, trigraph, three-letter word's second cipher character with 'h'
                            if (extractedKey[7] == '*' && reverseKey[getCipherCharacterIndex(c2)] == '*')
                            {
                                extractedKey[7] = c2;
                                reverseKey[getCipherCharacterIndex(c2)] = 'h';
                                substitutionsFound++;
                            }
                            //substituting most frequent bigraph, trigraph, three-letter word's third cipher character with 'e'
                            if (extractedKey[4] == '*' && reverseKey[getCipherCharacterIndex(c3)] == '*')
                            {
                                extractedKey[4] = c3;
                                reverseKey[getCipherCharacterIndex(c3)] = 'e';
                                substitutionsFound++;
                            }
                            break;
                        }
                    }
                }
                if (flag)
                    break;
            }
            if (flag)
                break;
        }
    }

    //using 'to' being one of the most frequent two letter word to find 'o' if 't' is recovered
    //checking if 't' is recovered
    if (extractedKey[19] != '*')
        for (sIt = twoLettersWordFreq.begin(); sIt != twoLettersWordFreq.end(); ++sIt)
            if (sIt->first[0] == extractedKey[19])
            {
                //substituting most frequent two-letter word's (starting with character substituted for 't') second cipher character with 'o'
                if (extractedKey[14] == '*' && reverseKey[getCipherCharacterIndex(sIt->first[1])] == '*')
                {
                    extractedKey[14] = sIt->first[1];
                    reverseKey[getCipherCharacterIndex(sIt->first[1])] = 'o';
                    substitutionsFound++;
                }
                break;
            }

    //using 'any' being one of the most frequent three letter word to find 'y' if 'a', 'n' and 'd' are recovered
    //checking if 'a', 'n' and 'd' are recovered
    if (extractedKey[0] != '*' && extractedKey[13] != '*' && extractedKey[3] != '*')
        for (sIt = threeLettersWordFreq.begin(); sIt != threeLettersWordFreq.end(); ++sIt)
            if (sIt->first[0] == extractedKey[0] && sIt->first[1] == extractedKey[13] && sIt->first[2] != extractedKey[3])
            {
                //substituting most frequent three-letter word's (starting with characters substituted for 'an' and third character not being substituted for 'd') third cipher character with 'y'
                if (extractedKey[24] == '*' && reverseKey[getCipherCharacterIndex(sIt->first[2])] == '*')
                {
                    extractedKey[24] = sIt->first[2];
                    reverseKey[getCipherCharacterIndex(sIt->first[2])] = 'y';
                    substitutionsFound++;
                }
                break;
            }

    //using 'with' being one of the most frequent four-letter word to find 'w' and 'i' if 't' and 'h' are recovered
    //checking if 't' and 'h' are recovered
    if (extractedKey[19] != '*' && extractedKey[7] != '*')
        for (sIt = fourLettersWordFreq.begin(); sIt != fourLettersWordFreq.end(); ++sIt)
            if (sIt->first[2] == extractedKey[19] && sIt->first[3] == extractedKey[7])
            {
                //substituting most frequent four-letter word's (ending with character substituted for 'th') first cipher character with 'w'
                if (extractedKey[22] == '*' && reverseKey[getCipherCharacterIndex(sIt->first[0])] == '*')
                {
                    extractedKey[22] = sIt->first[0];
                    reverseKey[getCipherCharacterIndex(sIt->first[0])] = 'w';
                    substitutionsFound++;
                }
                //substituting most frequent four-letter word's (ending with character substituted for 'th') second cipher character with 'i'
                if (extractedKey[8] == '*' && reverseKey[getCipherCharacterIndex(sIt->first[1])] == '*')
                {
                    extractedKey[8] = sIt->first[1];
                    reverseKey[getCipherCharacterIndex(sIt->first[1])] = 'i';
                    substitutionsFound++;
                }
                break;
            }

    //using 'for' being one of the most frequent three-letter word to find 'f' and 'r' if 'o' is recovered
    //checking if 'o' is recovered
    if (extractedKey[14] != '*')
        for (sIt = threeLettersWordFreq.begin(); sIt != threeLettersWordFreq.end(); ++sIt)
            if (sIt->first[1] == extractedKey[14] && sIt->first[0] != extractedKey[13])
            {
                //substituting most frequent three-letter word's (with middle character substituted for 'o') first cipher character with 'f'
                if (extractedKey[5] == '*' && reverseKey[getCipherCharacterIndex(sIt->first[0])] == '*')
                {
                    extractedKey[5] = sIt->first[0];
                    reverseKey[getCipherCharacterIndex(sIt->first[0])] = 'f';
                    substitutionsFound++;
                }
                //substituting most frequent three-letter word's (with middle character substituted for 'o') third cipher character with 'r'
                if (extractedKey[17] == '*' && reverseKey[getCipherCharacterIndex(sIt->first[2])] == '*')
                {
                    extractedKey[17] = sIt->first[2];
                    reverseKey[getCipherCharacterIndex(sIt->first[2])] = 'r';
                    substitutionsFound++;
                }
                break;
            }

    //**************************************************Dictionary Attack**************************************************

    //segmenting words as per their lengths
    string word = "";
    int substitutedCharactersFound;
    vector<string> fiveLengthWords, sixLengthWords, sevenLengthWords, eightLengthWords, nineLengthWords, tenLengthWords, moreThanTenLengthWords;
    for (i = 0; i < cipherText.size() + 1; ++i)
    {
        //checking whether we have reached end of the cipher text or ith character is not a predefined cipher text character
        if ((i == cipherText.size() || !isCipherCharacter(cipherText[i])))
        {
            if (word.length() >= 5)
            {
                switch (word.length())
                {
                case 5:
                    if (!findStringVector(fiveLengthWords, word))
                        fiveLengthWords.push_back(word);
                    break;
                case 6:
                    if (!findStringVector(sixLengthWords, word))
                        sixLengthWords.push_back(word);
                    break;
                case 7:
                    if (!findStringVector(sevenLengthWords, word))
                        sevenLengthWords.push_back(word);
                    break;
                case 8:
                    if (!findStringVector(eightLengthWords, word))
                        eightLengthWords.push_back(word);
                    break;
                case 9:
                    if (!findStringVector(nineLengthWords, word))
                        nineLengthWords.push_back(word);
                    break;
                case 10:
                    if (!findStringVector(tenLengthWords, word))
                        tenLengthWords.push_back(word);
                    break;
                default:
                    if (!findStringVector(moreThanTenLengthWords, word))
                        moreThanTenLengthWords.push_back(word);
                    break;
                }
            }
            word = "";
        }
        else
            word += cipherText[i];
    }

    bool updatesMadeFlag = true;
    //applying dictionary attack either till updates are being made or till we did find all the cipher characters in the given cipher text
    while (updatesMadeFlag && substitutionsFound != singleLetterFreq.size())
    {
        updatesMadeFlag = false;
        // dictionary attack over 5 letter words
        for (auto word : fiveLengthWords)
        {
            substitutedCharactersFound = 0;
            //finding the number of characters which are already substituted
            for (i = 0; i < 5; ++i)
                if (reverseKey[getCipherCharacterIndex(word[i])] != '*')
                    substitutedCharactersFound++;
            //checking is number of substituted words are greater than half the characters or not, just to be sure we are not considering a wrong word for the given cipher text word
            if (substitutedCharactersFound > 2 && substitutedCharactersFound < 5)
                for (auto dictWord : commonFiveLetterWords)
                {
                    flag = true;
                    //checking the compatibility of dictionary word along with the cipher text word
                    for (i = 0; i < 5; ++i)
                    {
                        flag = flag && (reverseKey[getCipherCharacterIndex(word[i])] == '*' || reverseKey[getCipherCharacterIndex(word[i])] == dictWord[i]);
                        if (!flag)
                            break;
                    }
                    //if word proves to be compatible, then we substitute words accordingly
                    if (flag)
                    {
                        for (i = 0; i < 5; ++i)
                            //substituting the non-substituted plain-text characters with the corresponding cipher-text characters according to dictionary word and cipher-text word
                            if (extractedKey[(int)dictWord[i] - 97] == '*' && reverseKey[getCipherCharacterIndex(word[i])] == '*')
                            {
                                extractedKey[(int)dictWord[i] - 97] = word[i];
                                reverseKey[getCipherCharacterIndex(word[i])] = dictWord[i];
                                substitutionsFound++;
                                updatesMadeFlag = true;
                            }
                        break;
                    }
                }
        }

        // dictionary attack over 6 letter words
        for (auto word : sixLengthWords)
        {
            substitutedCharactersFound = 0;
            //finding the number of characters which are already substituted
            for (i = 0; i < 6; ++i)
                if (reverseKey[getCipherCharacterIndex(word[i])] != '*')
                    substitutedCharactersFound++;
            //checking is number of substituted words are greater than half the characters or not, just to be sure we are not considering a wrong word for the given cipher text word
            if (substitutedCharactersFound > 2 && substitutedCharactersFound < 6)
                for (auto dictWord : commonSixLetterWords)
                {
                    flag = true;
                    //checking the compatibility of dictionary word along with the cipher text word
                    for (i = 0; i < 6; ++i)
                    {
                        flag = flag && (reverseKey[getCipherCharacterIndex(word[i])] == '*' || reverseKey[getCipherCharacterIndex(word[i])] == dictWord[i]);
                        if (!flag)
                            break;
                    }
                    //if word proves to be compatible, then we substitute words accordingly
                    if (flag)
                    {
                        for (i = 0; i < 6; ++i)
                            //substituting the non-substituted plain-text characters with the corresponding cipher-text characters according to dictionary word and cipher-text word
                            if (extractedKey[(int)dictWord[i] - 97] == '*' && reverseKey[getCipherCharacterIndex(word[i])] == '*')
                            {
                                extractedKey[(int)dictWord[i] - 97] = word[i];
                                reverseKey[getCipherCharacterIndex(word[i])] = dictWord[i];
                                substitutionsFound++;
                                updatesMadeFlag = true;
                            }
                        break;
                    }
                }
        }

        // dictionary attack over 7 letter words
        for (auto word : sevenLengthWords)
        {
            substitutedCharactersFound = 0;
            //finding the number of characters which are already substituted
            for (i = 0; i < 7; ++i)
                if (reverseKey[getCipherCharacterIndex(word[i])] != '*')
                    substitutedCharactersFound++;
            //checking is number of substituted words are greater than half the characters or not, just to be sure we are not considering a wrong word for the given cipher text word
            if (substitutedCharactersFound > 3 && substitutedCharactersFound < 7)
                for (auto dictWord : commonSevenLetterWords)
                {
                    flag = true;
                    //checking the compatibility of dictionary word along with the cipher text word
                    for (i = 0; i < 7; ++i)
                    {
                        flag = flag && (reverseKey[getCipherCharacterIndex(word[i])] == '*' || reverseKey[getCipherCharacterIndex(word[i])] == dictWord[i]);
                        if (!flag)
                            break;
                    }
                    //if word proves to be compatible, then we substitute words accordingly
                    if (flag)
                    {
                        for (i = 0; i < 7; ++i)
                            //substituting the non-substituted plain-text characters with the corresponding cipher-text characters according to dictionary word and cipher-text word
                            if (extractedKey[(int)dictWord[i] - 97] == '*' && reverseKey[getCipherCharacterIndex(word[i])] == '*')
                            {
                                extractedKey[(int)dictWord[i] - 97] = word[i];
                                reverseKey[getCipherCharacterIndex(word[i])] = dictWord[i];
                                substitutionsFound++;
                                updatesMadeFlag = true;
                            }
                        break;
                    }
                }
        }

        // dictionary attack over 8 letter words
        for (auto word : eightLengthWords)
        {
            substitutedCharactersFound = 0;
            //finding the number of characters which are already substituted
            for (i = 0; i < 8; ++i)
                if (reverseKey[getCipherCharacterIndex(word[i])] != '*')
                    substitutedCharactersFound++;
            //checking is number of substituted words are greater than half the characters or not, just to be sure we are not considering a wrong word for the given cipher text word
            if (substitutedCharactersFound > 3 && substitutedCharactersFound < 8)
                for (auto dictWord : commonEightLetterWords)
                {
                    flag = true;
                    //checking the compatibility of dictionary word along with the cipher text word
                    for (i = 0; i < 8; ++i)
                    {
                        flag = flag && (reverseKey[getCipherCharacterIndex(word[i])] == '*' || reverseKey[getCipherCharacterIndex(word[i])] == dictWord[i]);
                        if (!flag)
                            break;
                    }
                    //if word proves to be compatible, then we substitute words accordingly
                    if (flag)
                    {
                        for (i = 0; i < 8; ++i)
                            //substituting the non-substituted plain-text characters with the corresponding cipher-text characters according to dictionary word and cipher-text word
                            if (extractedKey[(int)dictWord[i] - 97] == '*' && reverseKey[getCipherCharacterIndex(word[i])] == '*')
                            {
                                extractedKey[(int)dictWord[i] - 97] = word[i];
                                reverseKey[getCipherCharacterIndex(word[i])] = dictWord[i];
                                substitutionsFound++;
                                updatesMadeFlag = true;
                            }
                        break;
                    }
                }
        }

        // dictionary attack over 9 letter words
        for (auto word : nineLengthWords)
        {
            substitutedCharactersFound = 0;
            //finding the number of characters which are already substituted
            for (i = 0; i < 9; ++i)
                if (reverseKey[getCipherCharacterIndex(word[i])] != '*')
                    substitutedCharactersFound++;
            //checking is number of substituted words are greater than half the characters or not, just to be sure we are not considering a wrong word for the given cipher text word
            if (substitutedCharactersFound > 4 && substitutedCharactersFound < 9)
                for (auto dictWord : commonNineLetterWords)
                {
                    flag = true;
                    //checking the compatibility of dictionary word along with the cipher text word
                    for (i = 0; i < 9; ++i)
                    {
                        flag = flag && (reverseKey[getCipherCharacterIndex(word[i])] == '*' || reverseKey[getCipherCharacterIndex(word[i])] == dictWord[i]);
                        if (!flag)
                            break;
                    }
                    //if word proves to be compatible, then we substitute words accordingly
                    if (flag)
                    {
                        for (i = 0; i < 9; ++i)
                            //substituting the non-substituted plain-text characters with the corresponding cipher-text characters according to dictionary word and cipher-text word
                            if (extractedKey[(int)dictWord[i] - 97] == '*' && reverseKey[getCipherCharacterIndex(word[i])] == '*')
                            {
                                extractedKey[(int)dictWord[i] - 97] = word[i];
                                reverseKey[getCipherCharacterIndex(word[i])] = dictWord[i];
                                substitutionsFound++;
                                updatesMadeFlag = true;
                            }
                        break;
                    }
                }
        }

        // dictionary attack over 10 letter words
        for (auto word : tenLengthWords)
        {
            substitutedCharactersFound = 0;
            //finding the number of characters which are already substituted
            for (i = 0; i < 10; ++i)
                if (reverseKey[getCipherCharacterIndex(word[i])] != '*')
                    substitutedCharactersFound++;
            //checking is number of substituted words are greater than half the characters or not, just to be sure we are not considering a wrong word for the given cipher text word
            if (substitutedCharactersFound > 5 && substitutedCharactersFound < 10)
                for (auto dictWord : commonTenLetterWords)
                {
                    flag = true;
                    //checking the compatibility of dictionary word along with the cipher text word
                    for (i = 0; i < 10; ++i)
                    {
                        flag = flag && (reverseKey[getCipherCharacterIndex(word[i])] == '*' || reverseKey[getCipherCharacterIndex(word[i])] == dictWord[i]);
                        if (!flag)
                            break;
                    }
                    //if word proves to be compatible, then we substitute words accordingly
                    if (flag)
                    {
                        for (i = 0; i < 10; ++i)
                            //substituting the non-substituted plain-text characters with the corresponding cipher-text characters according to dictionary word and cipher-text word
                            if (extractedKey[(int)dictWord[i] - 97] == '*' && reverseKey[getCipherCharacterIndex(word[i])] == '*')
                            {
                                extractedKey[(int)dictWord[i] - 97] = word[i];
                                reverseKey[getCipherCharacterIndex(word[i])] = dictWord[i];
                                substitutionsFound++;
                                updatesMadeFlag = true;
                            }
                        break;
                    }
                }
        }

        // dictionary attack over more than 10 letter words
        for (auto word : moreThanTenLengthWords)
        {
            substitutedCharactersFound = 0;
            //finding the number of characters which are already substituted
            for (i = 0; i < word.length(); ++i)
                if (reverseKey[getCipherCharacterIndex(word[i])] != '*')
                    substitutedCharactersFound++;
            //checking is number of substituted words are greater than half the characters or not, just to be sure we are not considering a wrong word for the given cipher text word
            if (substitutedCharactersFound > word.length() / 2 && substitutedCharactersFound < word.length())
                for (auto dictWord : commonMoreThanTenLetterWords)
                    if (dictWord.length() == word.length())
                    {
                        flag = true;
                        //checking the compatibility of dictionary word along with the cipher text word
                        for (i = 0; i < word.length(); ++i)
                        {
                            flag = flag && (reverseKey[getCipherCharacterIndex(word[i])] == '*' || reverseKey[getCipherCharacterIndex(word[i])] == dictWord[i]);
                            if (!flag)
                                break;
                        }
                        //if word proves to be compatible, then we substitute words accordingly
                        if (flag)
                        {
                            for (i = 0; i < word.length(); ++i)
                                //substituting the non-substituted plain-text characters with the corresponding cipher-text characters according to dictionary word and cipher-text word
                                if (extractedKey[(int)dictWord[i] - 97] == '*' && reverseKey[getCipherCharacterIndex(word[i])] == '*')
                                {
                                    extractedKey[(int)dictWord[i] - 97] = word[i];
                                    reverseKey[getCipherCharacterIndex(word[i])] = dictWord[i];
                                    substitutionsFound++;
                                    updatesMadeFlag = true;
                                }
                            break;
                        }
                    }
        }
    }

    //**************************************************Handling not substituted characters**************************************************
    //since, this program is highly dependent over the Heuristics for English language and also the dictionary of common words used in English, there are chances where all the cipher text characters present in the cipher-text are not substituted
    //hence, we just substitute the cipher-text characters for the remaining characters which are not substituted, either due to limitations of the program or due to absence in the cipher-text character
    j = 0;
    i = 0;
    while (i < 26)
    {
        if (extractedKey[i] == '*')
        {
            while (reverseKey[j] != '*')
                j++;
            extractedKey[i] = getCipherCharacterFromIndex(j);
            reverseKey[j] = char(i + 97);
        }
        i++;
    }

    //**************************************************Evaluating Plaintext based on the Deciphered Key**************************************************
    string decipheredPlaintext = "";

    //decrypting
    for (auto e : cipherText)
        decipheredPlaintext += isCipherCharacter(e) ? reverseKey[getCipherCharacterIndex(e)] : e;

    //**************************************************Printing Result**************************************************
    cout << "Ciphertext (Input):\n";
    cout << cipherText << "\n\n";
    cout << "Deciphered Plaintext:\n";
    cout << decipheredPlaintext << "\n\n";
    cout << "Deciphered Key:\n";
    cout << extractedKey << "\n\n";

    //**************************************************Outputing Result**************************************************
    ofstream fout;
    fout.open("./deciphered_plaintext.txt");
    fout << decipheredPlaintext;
    fout.close();

    fout.open("./deciphered_key.txt");
    fout << extractedKey;
    fout.close();

    return 0;
}