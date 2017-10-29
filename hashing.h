//
//  hashing.hpp
//  proj2b
//
//  Created by Vincent Bett on 11/25/16.
//  Copyright © 2016 Vincent Bett. All rights reserved.
//

#ifndef hashing_h
#define hashing_h

#include <stdio.h>
#include <iostream>
#include <functional>
#include <vector>
#include "wordStruct.h"

using namespace std;



class hashing
{
public:
    /*
     FUNCTION:
     PURPOSE:
     INPUT:
     OUTPUT
    */
    hashing();
    
    /*
     FUNCTION: desructor
     PURPOSE: to free the memmory
     INPUT: none
     OUTPUT: none
     */
    ~hashing();
    
    /*
     FUNCTION: CreateHash
     PURPOSE: to take a word and hash it to create a certain value
     INPUT: a string
     OUTPUT: an unsigned int
     */
    size_t CreateHash(string item);
    
    
    
    /*
     FUNCTION: getWord
     PURPOSE: to return location and file a word is located
     INPUT: a string
     OUTPUT: a struct that contains the word, filepath and the line location
     */
    words getWord(string key);
    
       
    /*
     FUNCTION: insert item
     PURPOSE: to take a word and a filepath and to put it in a certain
     place in the hash table
     INPUT: 3 strings, an unsigned int, a bool and an int
     OUTPUT: none
     */
    void insertItem(string item, string filePath, size_t value, int line,
                                 bool contained, string origi, int lineLoc);
    
    /*
     FUNCTION: linearProbe
     PURPOSE: to loop through the hash table and add a word struct into an empty
     index
     INPUT: a string, an unsigned int and a struct that contains a word a
     filepath and its line number
     OUTPUT: none
     */
    void linearProbe(string item, size_t value, NotConverted origi);
    
    /*
     FUNCTION: probeForUpper
     PURPOSE: to loop and add a struct to an empty index
     INPUT: a string and a struct that contains mixed case letters
     OUTPUT: none
     */
    void probeForUpper(string item, size_t value, converted conv);
    
    /*
     FUNCTION: insertline
     PURPOSE: to add the line to a vector that stores lines of word
     and to return an integer to that line.
     INPUT: a string
     OUTPUT: an int
     */
    int insertline(string line);
    
    /*
     FUNCTION: incrementNumlines
     PURPOSE: count up the number of lines
     INPUT: none
     OUTPUT: none
     */
    void incrementNumlines();
    
    /*
     FUNCTION: getTheLine
     PURPOSE: to return a string that is the line
     INPUT: an int
     OUTPUT: a string
     */
    string getTheLine(int pos );
    
    /*
     FUNCTION: insertCaps
     PURPOSE: To insert the words witm mixed case letters in the table
     INPUT: 3 strings, an unsigned int, a bool and an int
     OUTPUT: none
     */
    void insertCaps(string item, string filePath, size_t value, int line,
                                                 string origi, int  lineLoc);
    
    /*
     FUNCTION: insertAllLower
     PURPOSE: To insert the words with only case letters in the table
     INPUT:  3 strings, an unsigned int, a bool and an int
     OUTPUT: none
     */
    void insertAllLower(string item, string filePath, size_t value, 
                                                        int line, int  lineLoc);
    
    /*
     FUNCTION: probeexpand
     PURPOSE: To probe the expanded table and find an empty index to insert the
     word.
     INPUT: a string, an unsigned int. an array, two vectors and an integer
     OUTPUT: none
     */
    void probeExpand(string word, size_t indx, words arr[],
                                vector<NotConverted> originals,
                                        vector<converted> changed, 
                                                                int numTimes);
    
private:
    
    unsigned int tableSize;
    words *WordsFound;
    vector<string> lines;    
    int numlines;
    int loadFactor;
    int numElements;
    int indx2add;
    
    /*
     FUNCTION: initializeArray
     PURPOSE: to initialize an empty array
     INPUT: none
     OUTPUT: none.
     */
    void initializeArray();
    
    /*
     FUNCTION: CalculateLoadFactor
     PURPOSE: to calculate the load factor to determine when to expand
     INPUT: none
     OUTPUT: none
     */
    void CalculateLoadFactor();
    
    /*
     FUNCTION: incrementNumElements
     PURPOSE: increment the number of elements in the hash table
     INPUT: none
     OUTPUT: none
     */
    void incrementNumElements();
    
    /*
     FUNCTION: expand
     PURPOSE: to grow the table when the load factor is above 70%
     INPUT: none
     OUTPUT: none
     */
    void expand();
    
    /*
     FUNCTION: expandHelp
     PURPOSE: helper function for expand
     INPUT: a string, an unsigned int. an array, two vectors and an integer
     OUTPUT: none
     */
    void expandHelp(string word, size_t indx, words arr[], 
                    vector<NotConverted> originals,
                        vector<converted> changed, int numTimes);
    
    
    
    
};
#endif /* hashing_h */
