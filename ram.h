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
};

class FileOpenItem{

};

class FileOpenList{
private:

};

#endif //OS_RAM_H
