//
//  main.cpp
//  proj2b
//
//  Created by Vincent Bett on 11/25/16.
//  Copyright © 2016 Vincent Bett. All rights reserved.
//

#include <iostream>
#include <sstream>
#include "hashing.h"
#include "wordStruct.h"
#include "parser.h"

void getInput(string input, hashing *HashFunc);
void performCaseSensitiveSearch(string toFind, hashing *HashFunc);
void NonCaseSensitiveSearch(string toFind, hashing *HashFunc);
bool containsUpper(string word);
string toLower(string word);
void findWord(bool contained, hashing *HashFunc, words found, string toFind);
void search(bool insensitive, hashing *HashFunc, string ToSearch,
                                                         string caseSntv);

/*
 *FUNCTION: main
 *PURPOSE: To get user input and run the entire program
 */
int main(int argc, char *argv[] ) {
        if(argc != 2)
        {
                cerr<<"Usage:  gerp directory"<<endl;
                cerr<<"/t where:  directory is a valid directory"<<endl;
                return EXIT_FAILURE;
        }

        string Directory = argv[1];
        hashing HashFunc;
        parser Gerp(Directory, &HashFunc);
        string input = " ";
        while(not cin.eof() and input != "" and input != "@q" and
                                                         input != "@quit")
        {
                cout<<"Query? ";
                getline(cin, input);
                getInput(input, &HashFunc);
        }
        return 0;
}
/*
 *FUNCTION: getInput
 *PURPOSE: to extract the word to be searched and to determine
 whether it's going to be case sensitive or not.
 *INPUT: a string and a pointer to the hashing class
 *OUTPUT: none
 */

void getInput(string input, hashing *HashFunc)
{
        string ToSearch = "";
        string caseSntv = "";
        bool insensitive = false;
        
        if(input == "" or input == "@q" or input =="@quit")
        {
                cout<<endl;
                cout <<"Goodbye! Thank you and have a nice day."<<endl;
                return;
        }
        else
        
        {

                for(unsigned int i = 0; i<input.length(); i++)
                {
                        caseSntv+=input[i];
                        if(caseSntv =="@i " or caseSntv == "@insensitive ")
                        {
                                insensitive = true;
                                for(unsigned int j = i+1; j<input.length(); j++)
                                {
                                        ToSearch+=input[j];
                                }   
                        }
                }

        }

        search(insensitive, HashFunc, ToSearch, caseSntv);
}

/*
FUNCTION: search
PURPOSE: to look for a word in the hash table
INPUT: a bool a pointer to the hasher and two strings
OUTPUT: none
*/
void search(bool insensitive, hashing *HashFunc, string ToSearch,
                                                         string caseSntv)
{
        if(insensitive)
        {
                // Perform insensitive search
                NonCaseSensitiveSearch(ToSearch, HashFunc);
        }
        else
        {
                // Perform a case sensitive search
                performCaseSensitiveSearch(caseSntv, HashFunc);
        }

}

/*
 *FUNCTION: performCaseSensitiveSearch
 *PURPOSE: to perform an case sensitive search for a word and to
 print it out if found.
 *INPUT: a string to be found and a pointer to the hashing class
 *OUTPUT: none
 */

void performCaseSensitiveSearch(string toFind, hashing *HashFunc)
{
        words found;
        string AllLower;
        AllLower = toFind;
        bool containedupper = containsUpper(toFind);
        if(containedupper)
        {
                AllLower = toLower(toFind);
        }

        found = HashFunc->getWord(AllLower);

        if(found.numtimes == -1)
        {
                cout<<toFind << " NOT FOUND. try @insensitive or @i "<<endl;
        }
        else
        {
                findWord(containedupper, HashFunc, found, toFind);
        }
}
/*
FUNCTION: findword
PURPOSE: print out the line that has the queried word
INPUT: a bool, a ponter to a class
OUTPUT:
*/
void findWord(bool contained, hashing *HashFunc, words found, string toFind)
{
        // If the initial queried word had an upper case letter
        // Check the vector with converted upper case.
        if(contained)
        {
                for(unsigned int i = 0; i< found.changed.size(); i++)
                {
                   if(found.changed[i].word == toFind)
                   {
                
                   string line = HashFunc->getTheLine(found.changed[i].linefrm);
                   cout<<found.changed[i].path<<":";
                   cout<<found.changed[i].line<<" "<< line <<endl;
                   }
                }
        }
        // print out the unchanged words.
        else
        {
                        string prevline = "";
                        string prevpath = "";
                        int prevlinenum = 0;
                for(unsigned int j = 0; j<found.originals.size(); j++)
                {
                string line = HashFunc->getTheLine(found.originals[j].linefrm);
                if(line != prevline or found.originals[j].path != prevpath or
                                    found.originals[j].line != prevlinenum)
                {
                        cout<<found.originals[j].path<<":";
                        cout<<found.originals[j].line<<" "<<line<<endl;
                }
                prevline = line;
                prevpath = found.originals[j].path;
                prevlinenum = found.originals[j].line; 
                }
        }
}

/*
 *FUNCTION: containsUpper
 *PURPOSE: check if a word contains an upper case
 letter.
 *INPUT: a string
 *OUTPUT: a bool
 */

bool containsUpper(string word)
{
        for(unsigned int i =0; i <word.length(); i++)
        {
                char c = word[i];
                if(isupper(c))
                        return true;
        }
        return false;


}

/*
 *FUNCTION: toLower
 *PURPOSE: to convert a word to all lower case
 *INPUT: a string
 *OUTPUT: a string
 */

string toLower(string word)
{
        string converted;
        for(unsigned int i =0; i <word.length(); i++)
        {
                char c = word[i];
                if(isupper(c))
                {
                        c = tolower(c);
                }

                converted+=c;
        }
        return converted;

}

/*
 *FUNCTION: NonCaseSensitiveSearch
 *PURPOSE: to perform an case sensitive search for a word and to
 print it out if found
 *INPUT: a string to be found and a pointer to the hashing class
 *OUTPUT: none
 */

void NonCaseSensitiveSearch(string toFind, hashing *HashFunc)
{
        string AllLower = toLower(toFind);
        words found;
        found = HashFunc->getWord(AllLower);
        // Word not found
        if(found.numtimes == -1)
        {
                cout<<toFind << " NOT FOUND. try @insensitive or @i "<<endl;
        }
        // Print out both upper and lower case
        else
        {
                string prevline = "";
                string prevpath = "";
                int prevlinenum = 0;
                for(unsigned int j = 0; j<found.originals.size(); j++)
                {
                string line  = HashFunc->getTheLine(found.originals[j].linefrm);
                if(line != prevline or found.originals[j].path != prevpath or
                                found.originals[j].line != prevlinenum)
                {
                        cout<<found.originals[j].path<<":";
                        cout<<found.originals[j].line<<" "<<line<<endl;
                }
                 prevline = line;
                 prevpath = found.originals[j].path;
                 prevlinenum = found.originals[j].line;
                }
                for(unsigned int i = 0; i<found.changed.size(); i++)
                {
                string line2  = HashFunc->getTheLine(found.changed[i].linefrm);
                cout<<found.changed[i].path<<":";
                cout<<found.changed[i].line<<" "<<line2<<endl;   
                }

        }
}
