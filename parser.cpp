//
//  parser.cpp
//  proj2b
//
//  Created by Vincent Bett on 11/26/16.
//  Copyright © 2016 Vincent Bett. All rights reserved.
//

#include "parser.h"

/*
 FUNCTION: constructor
 PURPOSE: fo initialize the class.
 INPUT: an int and a pointer to a hashing class
 OUTPUT: none
 */
parser::parser(string initDir, hashing *hasher)
{
        FSTree tree(initDir);
        root = tree.getRoot();
        filepath = "";
        hashFunc = hasher;
        IndexFiles();

}

/*
 FUNCTION: destructor
 PURPOSE: to free up memmory
 INPUT: none
 OUTPUT: none
 */
parser::~parser()
{

}

/*
 FUNCTION: updateFilepath
 PURPOSE: to increase the file path as the tree traverses deeper
 INPUT: a pointer
 OUTPUT: none
 */
void parser::updateFilepath(DirNode *node)
{
        filepath += node->getName();
        filepath+="/";
}

/*
 FUNCTION: getFiles
 PURPOSE: to get the files by following the path
 INPUT: a pointer
 OUTPUT: none
 */
void parser::getFiles(DirNode *root, string pathN)
{
        int numFiles = root->numFiles();
        for(int i =0; i < numFiles; i++)
        {
                string path = pathN;
                string Filename = root->getFile(i);
                path+=Filename;
                openFiles(path);
        }

}

/*
 FUNCTION: traverseDir
 PURPOSE: to det deeper into the directories
 INPUT: a pointer and a string
 OUTPUT: none
 */
void parser::traverseDir(DirNode *root, string filepath)
{
        string fullpath;
        string path = filepath;
        path += root->getName();
        path+="/";
        fullpath = path;

        if(root->isEmpty())
        {
                return;
        }
        if(root->hasFiles())
        {
                //get the files.
                getFiles(root, fullpath);

        }
        if(root->hasSubDir())
        {
                int numSubs = root->numSubDirs();
                // Traverse the subDirectories;
                for(int j = 0; j< numSubs; j++)
                {
                        DirNode *next = root->getSubDir(j);
                        traverseDir(next, fullpath);
                }
        }

}


/*
 FUNCTION: openFiles
 PURPOSE: to opend the found files
 INPUT: a string
 OUTPUT: none
 */
void parser::openFiles(string pathName)
{
        ifstream input;
        input.open(pathName);
        if (not input.is_open()) {
                cerr << "Unable to open " << pathName << endl;
                return;
        }
        readFiles(input, pathName);
}


/*
 FUNCTION: readFiles
 PURPOSE: to open the files
 INPUT: a pointer and a string
 OUTPUT: none
 */
void parser::readFiles(istream &infile, string pathname)
{
        string word;
        int lineLoc;
        int lineNum = 0;
        string line;
        while(not infile.eof())
        {
                getline(infile, line);
                lineLoc = hashFunc->insertline(line);
                lineNum++;
                istringstream wrd(line);
                while(wrd >> word)
                {
                        string origi = word;
                        bool contains = containsUpper(word);
                        if(contains)
                        {
                                word = convertToLower(word);
                        }
                       size_t value = hashFunc->CreateHash(word);
                        hashFunc->insertItem(word, pathname, value, lineNum,
                                                 contains, origi, lineLoc);
                }
        }

}

/*
 FUNCTION: containsUpper
 PURPOSE: to check if a word contains upper case
 INPUT: a string
 OUTPUT: a bool
 */
bool parser::containsUpper(string word)
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
 FUNCTION: convertToLower
 PURPOSE: to convert the word to all lower case
 INPUT: a string
 OUTPUT: a string
 */
string parser::convertToLower(string word)
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
 FUNCTION: indexFiles
 PURPOSE: to call traverse directory and start the indexing process
 INPUT: none
 OUTPUT: none
 */
void parser::IndexFiles()
{
        traverseDir(root, filepath);
}
