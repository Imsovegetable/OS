//
// Created by Chen Yining on 2021/5/26.
//
#include<iostream>
#include<fstream>
#include<string>
#include "INode.h"
using namespace std;


int CaculateFileSize(string filename){
    ifstream file(filename);
    if(!file.is_open())
        return -1;
    string t = "";
    fin >> noskipws >> t;
    return t.size();
}




