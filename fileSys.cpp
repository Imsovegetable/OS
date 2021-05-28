//
// Created by 旧城筱雨 on 2021/5/28.
//

#include "fileSys.h"

void SuperBlock::createFile(const string& fileName)
{
    //为新建的文件开辟一个空闲的i结点
    int i = iNodeList.getFreeInodeNum();
    if(i == -1)
    {
        cout << "I-nodes have been run out\n";
        return;
    }
    //为当前的目录的map添加文件的键值对
    current_dir->addItem(fileName, i);
    //写入内存表中
    INode newInode(0, getcurrentTime(), getcurrentTime(), current_user->username);
    if(iNodeList.addNewINode(newInode, i))
    {
        free_inode--;
    }
}

void fileSystem::fileCreate(const string& fileName)
{
    //遍历current_dir的所有指向的文件的i结点，查找是否已经有当前这个文件名了,如果有输出错误
    if(current_dir->checkItem(fileName))
    {
        cout << "the file '" << fileName << "' has already existed\n";
        return ;
    }
    superBlock.createFile(fileName);
}