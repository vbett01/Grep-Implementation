//
//  hashing.cpp
//  proj2b
//
//  Created by Vincent Bett on 11/25/16.
//  Copyright © 2016 Vincent Bett. All rights reserved.
//

#include "hashing.h"


/*
FUNCTION: constructor
PURPOSE: To initialize the private memebers and to 
declare an empty table
INPUT: none
OUTPUT: none
*/
hashing::hashing()
{
        tableSize = 10000000;
        numlines = 0;
        indx2add = 0;
        WordsFound = new words[tableSize];
        numElements = 0;
        loadFactor = 0;
        initializeArray();
}



/*
 FUNCTION: insertline
 PURPOSE: to add the line to a vector that stores lines of word
 and to return an integer to that line.
 INPUT: a string
 OUTPUT: an int
 */
int hashing::insertline(string line)
{
        indx2add = numlines;
        lines.push_back(line);
        incrementNumlines();
        return indx2add;

}

/*
 FUNCTION: getTheLine
 PURPOSE: to return a string that is the line
 INPUT: an int
 OUTPUT: a string
 */
string hashing::getTheLine(int pos)
{
        return lines[pos];
}

/*
 FUNCTION: incrementNumlines
 PURPOSE: count up the number of lines
 INPUT: none
 OUTPUT: none
 */
void hashing::incrementNumlines()
{
        numlines++;
}


/*
FUNCTION: initializeArray
PURPOSE: to initialize an empty array
INPUT: none
OUTPUT: none.
*/
void hashing::initializeArray()
{
        for (size_t i = 0; i < tableSize; i++)
        {
                WordsFound[i].numtimes = -1;
        }
}

/*
FUNCTION: desructor
PURPOSE: to free the memmory
INPUT: none
OUTPUT: none
*/
hashing::~hashing()
{
        delete [] WordsFound;
}

/*
FUNCTION: CreateHash
PURPOSE: to take a word and hash it to create a certain value
INPUT: a string
OUTPUT: an unsigned int
*/
size_t hashing::CreateHash(string item)
{
        hash<string> hasher;

        return hasher(item) % tableSize;

}


/*
FUNCTION: incrementNumElements
PURPOSE: increment the number of elements in the hash table
INPUT: none
OUTPUT: none
*/
void hashing::incrementNumElements()
{
        numElements++;
}


/*
FUNCTION: insert item
PURPOSE: to take a word and a filepath and to put it in a certain 
place in the hash table
INPUT: 3 strings, an unsigned int, a bool and an int
OUTPUT: none
*/
void hashing::insertItem(string item, string filePath, size_t value,
                         int line, bool contained, string origi, int  lineLoc)
{
        if(loadFactor > 70)
        {
                expand();
        }
        if(contained)
        {
            insertCaps(item, filePath, value, line, origi, lineLoc);
        }
        else
        {
            insertAllLower(item, filePath, value, line, lineLoc);
        
        }
        incrementNumElements();
        CalculateLoadFactor();

}

/*
 FUNCTION: insertCaps
 PURPOSE: To insert the words witm mixed case letters in the table
 INPUT: 3 strings, an unsigned int, a bool and an int
 OUTPUT: none
 */
void hashing::insertCaps(string item, string filePath, size_t value,
                                         int line, string origi, int  lineLoc)
{
    converted conv;
    conv.word = origi;
    conv.path = filePath;
    conv.line = line;
    conv.linefrm = lineLoc;
    
    if(WordsFound[value].numtimes == -1)
    {
        WordsFound[value].word = item;
        WordsFound[value].changed.push_back(conv);
        WordsFound[value].numtimes = 1;
    }
    else if(WordsFound[value].word == item)
    {
        WordsFound[value].changed.push_back(conv);
    }
    else
    {
        probeForUpper(item, value, conv);
    }
    

}

/*
 FUNCTION: insertAllLower
 PURPOSE: To insert the words with only case letters in the table
 INPUT:  3 strings, an unsigned int, a bool and an int
 OUTPUT: none
*/
void hashing::insertAllLower(string item, string filePath, size_t value,
                                                         int line, int  lineLoc)
{
    NotConverted origi;
    origi.word = item;
    origi.path = filePath;
    origi.line = line;
    origi.linefrm = lineLoc;
    
    if(WordsFound[value].numtimes == -1)
    {
        WordsFound[value].word = item;
        WordsFound[value].originals.push_back(origi);
        WordsFound[value].numtimes = 1;
    }
    else if(WordsFound[value].word == item)
    {
        WordsFound[value].originals.push_back(origi);
    }
    else
    {
        linearProbe(item, value, origi);
    }

}

/*
FUNCTION: linearProbe
PURPOSE: to loop through the hash table and add a word struct into an empty indx
INPUT: a string, an unsigned int and a struct that contains a word a filepath
and its line number
OUTPUT: none
*/
void hashing::linearProbe(string item, size_t value, NotConverted origi)
{
      for(unsigned int i = (value+1)%tableSize; i !=value; i = (i+1)%tableSize)
        {
                if(WordsFound[i].numtimes == -1)
                {
                        WordsFound[i].word = item;
                        WordsFound[i].originals.push_back(origi);
                        WordsFound[i].numtimes = 1;
                        return;
                }
        }
}


/*
 FUNCTION: probeForUpper
 PURPOSE: to loop and add a struct to an empty index
 INPUT: a string and a struct that contains mixed case letters
 OUTPUT: none
 */
void hashing::probeForUpper(string item, size_t value, converted conv)
{
     for(unsigned int i = (value+1)%tableSize; i !=value; i = (i+1)%tableSize)
        {
                if(WordsFound[i].numtimes == -1)
                {
                        WordsFound[i].word = item;
                        WordsFound[i].numtimes = 1;
                        WordsFound[i].changed.push_back(conv);
                        return;
                }
        }

}

/*
FUNCTION: expand
PURPOSE: to grow the table when the load factor is above 70%
INPUT: none
OUTPUT: none
*/
void hashing::expand()
{
       unsigned int OldTableSize = tableSize;
        tableSize*=2;
        words *biggerTable = new words[tableSize];
        for(size_t i = 0; i < tableSize; i++)
        {
                biggerTable[i].numtimes = -1;
        }
        for (size_t j = 0; j < OldTableSize; j++)
        {
                if(WordsFound[j].numtimes != -1)
                {
                       size_t index = CreateHash(WordsFound[j].word);
                        expandHelp(WordsFound[j].word, index, biggerTable,
                                        WordsFound[j].originals,
                                                WordsFound[j].changed, 
                                                        WordsFound[j].numtimes);

                }
        }

        delete [] WordsFound;
        WordsFound = biggerTable;

}

/*
FUNCTION: expandHelp
PURPOSE: helper function for expand
INPUT: a string, an unsigned int. an array, two vectors and an integer
OUTPUT: none
*/
void hashing::expandHelp(string word, size_t indx, words arr[],
                vector<NotConverted> originals,vector<converted> changed, 
                                                                int numTimes)
{
        if(arr[indx].numtimes == -1)
        {
                arr[indx].word = word;
                arr[indx].numtimes = numTimes;
                for(size_t j = 0; j<originals.size(); j++)
                {
                        NotConverted origi = originals[j];
                        arr[indx].originals.push_back(origi);
                }
                for(size_t k = 0; k < changed.size(); k++)
                {
                        converted change = changed[k];
                        arr[indx].changed.push_back(change);
                }
        }
        else
        {
                //probe
                //come back here.
            probeExpand(word, indx, arr, originals, changed, numTimes);
        }

}

/*
 FUNCTION: probeexpand
 PURPOSE: To probe the expanded table and find an empty index to insert the
 word.
 INPUT: a string, an unsigned int. an array, two vectors and an integer
 OUTPUT: none
*/
void hashing::probeExpand(string word, size_t indx, words arr[],
                vector<NotConverted> originals,vector<converted> changed,
                                                                 int numTimes)
{
    for(size_t i = (indx+1)%tableSize; i != indx; i = (i+1)%tableSize)
    {
        if(arr[i].numtimes == -1)
        {
            arr[i].word = word;
            arr[i].numtimes = numTimes;
            for(size_t j = 0; j<originals.size(); j++)
            {
                NotConverted origi = originals[j];
                arr[i].originals.push_back(origi);
            }
            for(size_t k = 0; k < changed.size(); k++)
            {
                converted change = changed[k];
                arr[i].changed.push_back(change);
            }
            return;
        }
        
    }

}

/*
FUNCTION: CalculateLoadFactor
PURPOSE: to calculate the load factor to determine when to expand
INPUT: none
OUTPUT: none
*/
void hashing::CalculateLoadFactor()
{
        float elements  = numElements;
        float size = tableSize;
        loadFactor = (elements/size)*100;

}

/*
FUNCTION: getWord
PURPOSE: to return location and file a word is located
INPUT: a string
OUTPUT: a struct that contains the word, filepath and the line location
*/
words hashing::getWord(string item)
{

       size_t value = CreateHash(item);
        if(WordsFound[value].numtimes != -1)
        {
                if(WordsFound[value].word == item)
                {
                        return WordsFound[value];
                }
                else
                {
                        for(size_t i = (value+1)%tableSize; i !=value;
                                                         i = (i+1)%tableSize)
                        {
                                if(WordsFound[i].word == item)
                                {
                                        return WordsFound[i];
                                }
                        }
                }
        }
        words temp;
        temp.word = "NULL";
        temp.numtimes = -1;
        return temp;

}

