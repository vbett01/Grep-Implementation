//
//  wordStruct.h
//  proj2b
//
//  Created by Vincent Bett on 11/25/16.
//  Copyright © 2016 Vincent Bett. All rights reserved.
//

#ifndef wordStruct_h
#define wordStruct_h

#include <vector>


// Struct to hold all the converted words
struct converted
{
    std::string word;
    std::string path;
    int line;
    int linefrm;
};

// struct to hold all the original words
struct NotConverted
{
    std::string word;
    std::string path;
    int line;
    int linefrm;
};

// struct to store all the word information.
struct words{
    
    std::string word;
    int numtimes;
    std::vector<NotConverted> originals;
    std::vector<converted> changed;
};

#endif /* wordStruct_h */
