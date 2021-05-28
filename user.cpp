//
// Created by 旧城筱雨 on 2021/5/28.
//

#include "user.h"

user* current_user;

int Users::calculateFileSize(const string& filename)
{
    ifstream file(filename);
    if(!file.is_open())
        return -1;
    string t;
    file >> noskipws >> t;
    return t.size();
}

void Users::readUserList()
{
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

bool Users::IsExistedAuthor(const string& username)
{
    readUserList();
    for(auto & i : userList){
        if(i.username == username){
            return true;
        }
    }
    return false;

}

//bool Users::fileIsAuthor(const string& filename, const string& username){
//
//
//}

void Users::createUser(const string& username, const string& password)
{
    if(!IsExistedAuthor(username)){
        user tmp;
        tmp.username = username;
        tmp.password = password;
        userList.push_back(tmp);
        //    file<<tmp.username<<endl;
        //    file<<tmp.password<<endl;
    }
}

void Users::saveUser()
{
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
