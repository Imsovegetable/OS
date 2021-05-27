//
// Created by 旧城筱雨 on 2021/5/27.
//

#ifndef OS_DIRECTORY_H
#define OS_DIRECTORY_H

#include <bits/stdc++.h>
using namespace std;

class Directory{
private:
    //目录表
    map<string, int> directory;

public:
    // 添加一个目录项
    bool addItem(string filename, int id);
    // 删除一个目录项
    bool deleteItem(string filename);
    // 检查某一个目录项是否存在
    bool checkItem(string filename);
    // 获取某个目录项的i结点号
    int getItem(string filename);
    // 目录项重命名
    bool setFileName(string filename, string newName);
    // 返回大小
    int size();
    // 目录初始化
    void init(int idSelf, int idParent);
};

#endif //OS_DIRECTORY_H
