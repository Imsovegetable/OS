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
    INodeListInRam();

    int getFreeNode();

    bool loadNode(INode A, int id);

    INode freeNode(int id);

    int searchNode(int id);

    //xxx readSomeInfo(int id);

    bool updateInfo(int id); // 也可以考虑用复制构造函数更新

    bool saveInodes(); // 需要调磁盘Inode表的函数 或许要集成到文件系统里 而不是这里
};

class FileOpenItem{

};

class FileOpenList{
private:

};

#endif //OS_RAM_H
