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

bool IsExistedAuthor(const string& username){
    ifstream file("users.txt");
    if(!file.is_open()){
        cout<<"users.txt can not open in checkIsAuthor function "<<endl;
        return -1;
    }
    string line;
    while(getline(file, line)){
        user tmp;
        tmp.username = line;
        getline(file, line);
        tmp.password = line;
        userList.push_back(tmp);
    }
    for(auto & i : userList){
        if(i.username == username){
            return true;
        }
    }
    return false;

}


void createUser(const string& username, const string& password){
    ofstream file("users.txt");
    if(!file.is_open()){
        cout<<"users.txt can not open in createUser function "<<endl;
        return -1;
    }


}
