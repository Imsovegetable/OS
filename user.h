//
// Created by 旧城筱雨 on 2021/5/28.
//

#include<iostream>
#include<fstream>
#include <vector>
#include<string>
#include "INode.h"
#include "directory.h"

#ifndef OS_USER_H
#define OS_USER_H

//
// Created by Chen Yining on 2021/5/26.
//

using namespace std;

class User{
private:
    Directory* cur_dir = nullptr;
    string username = "";
    string password = "";
    bool state = false;
public:
    User();

    User(string un, string pw, Directory* dir = nullptr);
    // 获取用户名
    string getUsername();
    // 获取密码
    string getPassword();
    // 登录
    string login(string un, string pw);
    // 读取当前目录
    Directory* getCurDir();
    // 修改当前目录项
    void setCurDir(Directory* dir);
    // 检查状态
    bool check();
    // 登出
    void loginOut();

    void clear();
};

extern string current_user;
//把user的表读到用户数组中去
class Users{
private:
    int userListSize = 0;

public:
    vector<User> userList;
    //计算文件大小
    int calculateFileSize(const string& filename);
    // 读取用户列表
    void readUserList();
    //是否存在该用户
    bool IsExistedAuthor(const string& username);
    //新建用户
    void createUser(const string& username, const string& password);
    // 保存用户
    void saveUser();
    // 用户登录
    bool login(string username, string password);
    // 搜索用户
    int searchUser(string username);
    // 切换用户
    bool switchUser(string username);
    // 用户登出
    void loginOut();
    // 获取当前目录
    Directory* getCurDir();
    // 设置当前目录
    void setCurDir(Directory* dir);
};


#endif //OS_USER_H
