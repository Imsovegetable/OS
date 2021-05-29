//
// Created by 旧城筱雨 on 2021/5/27.
//
#include <bits/stdc++.h>
#include "GODNING.h"
#include "inode.h"

#ifndef OS_RAM_H
#define OS_RAM_H

using namespace std;

class INodeListInRam{
private:
    const int iNodeListCapacity = INODET_IN_RAM;
    int iNodeListSize = 0;
    INode iNodeList[INODET_IN_RAM];
    int iNodeNum[INODET_IN_RAM];
    int fileLock[INODET_IN_RAM]; // 文件锁,1为读锁,2为写锁

public:
    // 构造函数
    INodeListInRam();
    // 获取空的内存i结点
    int getFreeNode();
    // 加载一个i结点
    bool loadNode(INode A, int id);
    // 释放一个i结点
    INode freeNode(int id);
    // 寻找id所对应的内存i结点的下标
    int searchNode(int id);

    //xxx readSomeInfo(int id);

    bool updateInfo(int id);

    bool saveInodes();

    bool setLock(string username, int lock, int id);
};

// 文件打开项
class FileOpenItem{
private:
    unsigned offSet = 0;
    int linkN = 0;
    int flags = 0; // 打开文件的参数
    int mode = 0; // 创建文件的参数
    int id = -1; // inode号

public:
    FileOpenItem();
    // 复制构造函数
    FileOpenItem(FileOpenItem& ano);
    // 赋值构造函数
    FileOpenItem(int offset, int flags, int mode, int id);
    // 获取inode的id
    int getId();
    // 获取偏移量
    int getOffset();
    // 设置偏移量
    bool setOffset(int sign, int step);
    // 清空文件打开项
    void clear();
    // 获取链接数
    int getLink();
    // 增加链接
    void icrLink();
    // 减少链接
    void dcrLink();
};

// 系统文件打开表
class FileOpenList{
private:
    // 系统文件打开表最大项数
    const int fileOpenCapacity = MAX_FDS;
    // 系统文件表当前项数
    int fileOpenSize = 0;
    // 文件项
    FileOpenItem fileOpenList[MAX_FDS];

public:
    // 清空
    void clear();
    // 获取大小
    int size();
    // 删除某一项
    bool deleteItem(int id);
    // 删除引用
    bool deleteLink(int id);
    // 增加引用
    bool addLink(int id);
    // 添加某一项
    int addItem(int offset, int flags, int mode, int id);
    // 获取某一项的inode编号
    int getItemINode(int id);
    // 获取空闲块
    int getFreeItem();
};

class UserOpenItem{
private:
    int descriptor = -1;
    int id = -1;

public:
    UserOpenItem();

    UserOpenItem(int descriptor, int id);
    // 清空
    void clear();
    // 设置值
    void set(int descriptor, int id);
    // 获取描述符
    int getDescriptor();
    // 获取id
    int getId();
    // 检查是否可用
    bool check();
};

class UserOpenList{
private:
    string username = "";
    UserOpenItem iNodeToFile[MAX_USER_FD];

public:
    UserOpenList();
    // 赋值构造函数
    UserOpenList(string username);
    // 清空
    void clear();
    // 获取系统文件打开表下标
    int getFileId(int iNodeId);
    // 添加一个项
    bool addItem(int iNodeId, int fileId);
    // 删除一个项
    bool deleteItem(int iNodeId);
    // 寻找下标
    int searchId(int iNodeId);
    // 寻找空闲下标
    int searchFreeItem();
};

UserOpenList::UserOpenList(){}
// 赋值构造函数
UserOpenList::UserOpenList(string username)
: username(username){}
// 清空
void UserOpenList::clear()
{
    username = "";
    for(int i = 0; i < MAX_USER_FD; i++)
        iNodeToFile[i].clear();
}
// 获取系统文件打开表下标
int UserOpenList::getFileId(int iNodeId)
{
    int id = searchId(iNodeId);
    if(id == -1)
        return -1;
    return iNodeToFile[id].getId();
}
//寻找下标
int UserOpenList::searchId(int iNodeId)
{
    for(int i = 0; i < MAX_USER_FD; i++)
        if(iNodeToFile[i].getDescriptor() == iNodeId)
            return i;
    return -1;
}
// 寻找空闲下标
int UserOpenList::searchFreeItem()
{
    for(int i = 0; i < MAX_USER_FD; i++)
        if(iNodeToFile[i].check() == false)
            return i;
    return -1;
}
// 添加一个项
bool UserOpenList::addItem(int iNodeId, int fileId)
{
    int id = searchFreeItem();
    if(id == -1)
        return false;
    UserOpenItem t(iNodeId, fileId);
    iNodeToFile[id] = t;
}
// 删除一个项
bool UserOpenList::deleteItem(int iNodeId)
{
    int id = searchId(iNodeId);
    if(id == -1)
        return false;
    iNodeToFile[id].clear();
    return true;
}

#endif //OS_RAM_H
