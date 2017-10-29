//
//  parser.hpp
//  proj2b
//
//  Created by Vincent Bett on 11/26/16.
//  Copyright © 2016 Vincent Bett. All rights reserved.
//

#ifndef parser_h
#define parser_h

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <locale>
#include <string>

#include "FSTree.h"
#include "DirNode.h"
#include "hashing.h"

using namespace std;

class parser
{
public:
    /*
     FUNCTION: constructor
     PURPOSE: fo initialize the class.
     INPUT: an int and a pointer to a hashing class
     OUTPUT: none
     */
    parser(string initDir, hashing *hasher);
    
    /*
     FUNCTION: destructor
     PURPOSE: to free up memmory
     INPUT: none
     OUTPUT: none
     */
    ~parser();
    
    /*
     FUNCTION: updateFilepath
     PURPOSE: to increase the file path as the tree traverses deeper
     INPUT: a pointer
     OUTPUT: none
     */
    void updateFilepath(DirNode *node);
    
    /*
     FUNCTION: traverseDir
     PURPOSE: to det deeper into the directories
     INPUT: a pointer and a string
     OUTPUT: none
     */
    void traverseDir(DirNode *root, string filepath);
    
    /*
     FUNCTION: getFiles
     PURPOSE: to get the files by following the path
     INPUT: a pointer
     OUTPUT: none
     */
    void getFiles(DirNode *root, string path);
    
    /*
     FUNCTION: openFiles
     PURPOSE: to opend the found files
     INPUT: a string
     OUTPUT: none
     */
    void openFiles(string pathName);
    
    /*
     FUNCTION: readFiles
     PURPOSE: to open the files
     INPUT: a pointer and a string
     OUTPUT: none
     */
    void readFiles(istream &infile, string pathname);
    
    /*
     FUNCTION: indexFiles
     PURPOSE: to call traverse directory and start the indexing process
     INPUT: none
     OUTPUT: none
     */
    void IndexFiles();
    
    /*
     FUNCTION: containsUpper
     PURPOSE: to check if a word contains upper case
     INPUT: a string
     OUTPUT: a bool
     */
    bool containsUpper(string word);
    
    /*
     FUNCTION: convertToLower
     PURPOSE: to convert the word to all lower case
     INPUT: a string
     OUTPUT: a string
     */
    string convertToLower(string word);
    
    
    
    
    
    
private:
    string filepath;
    DirNode *root;
    hashing *hashFunc;
    
};
#endif /* parser_h */
