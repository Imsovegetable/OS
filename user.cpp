//
// Created by 旧城筱雨 on 2021/5/28.
//

#include "user.h"
#include <bits/stdc++.h>
string current_user = "";

User::User(){}

User::User(string un, string pw, Directory *dir)
: cur_dir(dir)
, username(un)
, password(pw){}
// 获取用户名
string User::getUsername()
{
    return username;
}
// 获取密码
string User::getPassword()
{
    return password;
}
// 登录
string User::login(string un, string pw)
{
    if(un == username && pw == password)
    {
        state = true;
        return username;
    }
    else
        return "";
}
// 获取当前目录
Directory* User::getCurDir()
{
    return cur_dir;
}
//设置当前目录
void User::setCurDir(Directory *dir)
{
    cur_dir = dir;
}
// 检查状态
bool User::check()
{
    return state;
}
// 登出
void User::loginOut()
{
    state = false;
}

// 删除对应用户
void User::clear() {
    cur_dir = nullptr;
    username = "";
    password = "";
    state = false;
}


//计算文件大小
int Users::calculateFileSize(const string& filename)
{
    ifstream file(filename);
    if(!file.is_open())
        return -1;
    string t;
    file >> noskipws >> t;
    return t.size();
}

// 读取用户列表
void Users::readUserList()
{
    ifstream file("users.txt");
    if(!file.is_open()){
        cout<<"users.txt can not open in checkIsAuthor function "<<endl;
        exit(0);
    }
    string line;
    int cnt;
    getline(file, line);
    userListSize = atoi(line.c_str());
    for(int i=0; i<userListSize; i++){
        getline(file, line);
        string username = line;
        getline(file, line);
        string password = line;
        User tmp(username, password);
        userList.push_back(tmp);
    }
}

//是否存在该用户
bool Users::IsExistedAuthor(const string& username)
{
//    readUserList();
    for(auto & i : userList){
        if(i.getUsername() == username){
            return true;
        }
    }
    return false;
}

//bool Users::fileIsAuthor(int inodeNum, const string& username){
//
//
//}

//新建用户
void Users::createUser(const string& username, const string& password)
{
    if(!IsExistedAuthor(username)){
        User tmp(username, password);
        userList.push_back(tmp);
        userListSize++;
        //    file<<tmp.username<<endl;
        //    file<<tmp.password<<endl;
    }
}

// 保存用户
void Users::saveUser()
{
    ofstream file("users.txt");
    if(!file.is_open()){
        cout<<"users.txt can not open in createUser function "<<endl;
        exit(0);
    }
    file << userList.size() << endl;
    for(auto & i : userList){
        file<<i.getUsername()<<endl;
        file<<i.getPassword()<<endl;
    }
    file.close();
}

//用户登录
bool Users::login(string username, string password)
{
    for(int i = 0; i < userListSize; i++)
    {
        if(userList[i].login(username, password) != "")
        {
            current_user = username;
            // 加载目录一类的
            return true;
        }
    }
    return false;
}
// 搜索用户
int Users::searchUser(string username)
{
    for(int i = 0; i < userListSize; i++)
    {
        if(userList[i].getUsername() == username)
            return i;
    }
    return -1;
}
// 切换用户
bool Users::switchUser(string username)
{
    int i = searchUser(username);
    if(i == -1)
        return false;
    if(userList[i].check())
    {
        current_user = userList[i].getUsername();
        return true;
    }
    else
        return false;
}
// 登出
void Users::loginOut()
{
    int i = searchUser(current_user);
    if(i == -1)
        return;
    userList[i].loginOut();
    current_user = "";
}
// 获取当前目录
Directory* Users::getCurDir()
{
    int i = searchUser(current_user);
    if(i == -1)
        return nullptr;
    return userList[i].getCurDir();
}
// 设置当前目录
void Users::setCurDir(Directory* dir)
{
    int i = searchUser(current_user);
    if(i == -1)
        return;
    userList[i].setCurDir(dir);
}