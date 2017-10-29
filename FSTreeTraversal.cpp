//
//  main.cpp
//  proj2a
//
//  Created by Vincent Bett on 11/17/16.
//  Copyright © 2016 Vincent Bett. All rights reserved.
//

#include <iostream>
#include "FSTree.h"
#include "DirNode.h"

using namespace std;


void traverseDir(DirNode *root, string filepath);
void addSubDirs(DirNode *root, DirNode *node);
void printFileNames(DirNode *root, string filepath);

int main(int argc, const char * argv[]) {
    
    if(argc<2)
    {
        cout<<"error"<<endl;
        return 0;
    }
    FSTree tree(argv[1]);
    
    DirNode *root;
    root = tree.getRoot();
    string filePath = "../";
    
    
    return 0;
}

void traverseDir(DirNode *root, string filepath)
{
    filepath+=root->getName();
    filepath+="/";
    
    if(root->isEmpty())
    {
        return;
    }
    if(root->hasFiles())
    {
        //print file name;
    }
    if(root->hasSubDir())
    {
        int numSubs = root->numSubDirs();
    
    // Traverse the subDirectories;
        for(int j = 0; j< numSubs; j++)
        {
            DirNode *next = root->getSubDir(j);
            traverseDir(next, filepath);
        }
    }
}

void addSubDirs(DirNode *root, DirNode *node )
{
    root->addSubDirectory(node);
}

void printFileNames(DirNode *root, string filepath)
{
    int numFiles = root->numFiles();
    for(int i = 0; i< numFiles; i++)
    {
        string name = root->getFile(i);
        filepath+=name;
        cout<<filepath<<endl;
        
    }
    
    
}