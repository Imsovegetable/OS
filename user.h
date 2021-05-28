//
// Created by 旧城筱雨 on 2021/5/28.
//

#include<iostream>
#include<fstream>
#include <vector>
#include<string>
#include "INode.h"

#ifndef OS_USER_H
#define OS_USER_H

//
// Created by Chen Yining on 2021/5/26.
//

using namespace std;

struct user{
    string username;
    string password;
};

extern user* current_user;
//把user的表读到用户数组中去
class Users{
public:
    vector<user> userList;

    int calculateFileSize(const string& filename);

    void readUserList();

    bool IsExistedAuthor(const string& username);

    void createUser(const string& username, const string& password);

    void saveUser();
};


#endif //OS_USER_H
