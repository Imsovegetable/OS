//
// Created by 旧城筱雨 on 2021/5/27.
//
#include <bits/stdc++.h>

#ifndef OS_DIRECTORY_H
#define OS_DIRECTORY_H


using namespace std;

class Directory{
private:
    //目录表
    map<string, int> directory;

public:
    //
    Directory();

    Directory(Directory&);

    Directory& operator=(const Directory&);
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
    // 清空目录
    void clear();
    // 显示信息
    void show()
    {
        cout << "\n——————————————————————————————\n";
        for(auto& it: directory)
            cout << it.first << " " << it.second << endl;
        cout << "——————————————————————————————\n";
    }
    //获取目录结点里面的文件个数
    int getFileNumFromDir();
    //将vector转换成string类型便于存储
    string save_as_string_dir();
};


#endif //OS_DIRECTORY_H
