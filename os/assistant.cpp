//
// Created by Chen Yining on 2021/5/26.
//
#include<iostream>
#include<fstream>
#include<string>
#include "INode.h"
using namespace std;


struct user{
    string username;
    string password;
};

//把user的表读到用户数组中去
vector<user> userList;

int CaculateFileSize(const string& filename){
    ifstream file(filename);
    if(!file.is_open())
        return -1;
    string t;
    file >> noskipws >> t;
    return t.size();
}

void readUserList(){
    ifstream file("users.txt");
    if(!file.is_open()){
        cout<<"users.txt can not open in checkIsAuthor function "<<endl;
        exit(0);
    }
    string line;
    while(getline(file, line)){
        user tmp;
        tmp.username = line;
        getline(file, line);
        tmp.password = line;
        userList.push_back(tmp);
    }
}




