//
// Created by Chen Yining on 2021/5/26.
//
#include<iostream>
#include<fstream>
#include <vector>
#include<string>
#include "INode.h"
#include "users.txt"
#include "assistant.cpp"
using namespace std;


bool IsExistedAuthor(const string& username){
//    ifstream file("users.txt");
//    if(!file.is_open()){
//        cout<<"users.txt can not open in checkIsAuthor function "<<endl;
//        return -1;
//    }
//    string line;
//    while(getline(file, line)){
//        user tmp;
//        tmp.username = line;
//        getline(file, line);
//        tmp.password = line;
//        userList.push_back(tmp);
//    }
    readUserList();
    for(auto & i : userList){
        if(i.username == username){
            return true;
        }
    }
    return false;

}

bool fileIsAuthor(const string& filename, const string& username){
    

}

void createUser(const string& username, const string& password){
    ofstream file("users.txt");
    if(!file.is_open()){
        cout<<"users.txt can not open in createUser function "<<endl;
        exit(0);
    }
    if(!IsExistedAuthor(username)){
        user tmp;
        tmp.username = username;
        tmp.password = password;
        userList.push_back(tmp);
        file<<tmp.username<<endl;
        file<<tmp.password<<endl;
    }
}
