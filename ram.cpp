//
// Created by 旧城筱雨 on 2021/5/27.
//

#include "ram.h"

INodeListInRam::INodeListInRam()
{
    for(int i = 0; i < INODET_IN_RAM; i++)
        iNodeNum[i] = -1;
}

int INodeListInRam::getFreeNode()
{
    for(int i = 0; i < INODET_IN_RAM; i++)
    {
        if(iNodeList[i].check())
        {
            return i;
        }
    }
}

bool INodeListInRam::loadNode(INode A, int id)
{
    int i = getFreeNode();
    iNodeList[i] = A;
    iNodeNum[i] = id;
}

INode INodeListInRam::freeNode(int id)
{
    int i = searchNode(id);
    INode t = iNodeList[i];
    iNodeList[i].clear();
    iNodeNum[i] = -1;
    return t;
}

int INodeListInRam::searchNode(int id)
{
    for(int i = 0; i < INODET_IN_RAM; i++)
        if(iNodeNum[i] == id)
            return i;
}