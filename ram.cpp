//
// Created by 旧城筱雨 on 2021/5/27.
//

#include "ram.h"

// 构造函数
INodeListInRam::INodeListInRam()
{
    for(int i = 0; i < INODET_IN_RAM; i++)
        iNodeNum[i] = -1;
}
// 获取空的内存i结点
int INodeListInRam::getFreeNode()
{
    for(int i = 0; i < INODET_IN_RAM; i++)
    {
        if(iNodeList[i].check())
        {
            return i;
        }
    }
    return -1;
}
// 加载一个i结点
bool INodeListInRam::loadNode(INode A, int id)
{
    int i = getFreeNode();
    if(i == -1)
        return false;
    iNodeList[i] = A;
    iNodeNum[i] = id;
    return true;
}
// 释放一个i结点
INode INodeListInRam::freeNode(int id)
{
    INode t;
    int i = searchNode(id);
    if(i == -1)
        return t;
    t = iNodeList[i];
    iNodeList[i].clear();
    iNodeNum[i] = -1;
    return t;
}
// 寻找id所对应的内存i结点的下标
int INodeListInRam::searchNode(int id)
{
    for(int i = 0; i < INODET_IN_RAM; i++)
        if(iNodeNum[i] == id)
            return i;
    return -1;
}