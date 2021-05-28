//
// Created by Chen Yining on 2021/5/26.
//
#include<iostream>
#include<fstream>
#include <vector>
#include<string>
#include "INode.h"
#include "users.txt"
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
    if(!IsExistedAuthor(username)){
        user tmp;
        tmp.username = username;
        tmp.password = password;
        userList.push_back(tmp);
    //    file<<tmp.username<<endl;
    //    file<<tmp.password<<endl;
    }
}

void saveUser(){
    ofstream file("users.txt");
    if(!file.is_open()){
        cout<<"users.txt can not open in createUser function "<<endl;
        exit(0);
    }
    for(auto & i : userList){
        file<<i.username<<endl;
        file<<i.password<<endl;
    }
    file.close();

}
