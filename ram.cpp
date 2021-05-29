//
// Created by 旧城筱雨 on 2021/5/27.
//

#include "ram.h"

// 构造函数
INodeListInRam::INodeListInRam()
{
    for(int i = 0; i < INODET_IN_RAM; i++)
        iNodeNum[i] = -1, fileLock[i] = 0;
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
    fileLock[i] = 0;
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
// 用户username对下标为id的inode对应的文件加锁
bool INodeListInRam::setLock(string username, int lock, int id)
{
    if(lock < 0 || lock > 2)
        return false;
    int i = searchNode(id);
    if(iNodeList[i].getUser() == username)
        fileLock[i] = lock;
    else
        return false;
    return true;
}



// 空构造函数
FileOpenItem::FileOpenItem(){}

// 复制构造函数
FileOpenItem::FileOpenItem(FileOpenItem &ano)
: offSet(ano.offSet)
, linkN(ano.linkN)
, flags(ano.flags)
, mode(ano.mode)
, id(ano.id){}

// 赋值构造函数
FileOpenItem::FileOpenItem(int offset, int flags, int mode, int id)
: offSet(offset)
, linkN(1)
, flags(flags)
, mode(mode)
, id(id){}

// 获取inode的id
int FileOpenItem::getId()
{
    return id;
}

// 获取偏移量
int FileOpenItem::getOffset()
{
    return offSet;
}

// 设置偏移量
bool FileOpenItem::setOffset(int sign, int step = 0)
{
    if(sign == 1) // sign=1表示追加
        offSet += step;
    else if(sign == 2) // sign=2表示回到队首
        offSet = 0;
    else
        return false;
    return true;
}

// 清空文件打开项
void FileOpenItem::clear()
{
    offSet = flags = mode = linkN = 0;
    id = -1;
}

// 获取链接数
int FileOpenItem::getLink()
{
    return linkN;
}

// 增加链接
void FileOpenItem::icrLink()
{
    linkN++;
}

// 减少链接
void FileOpenItem::dcrLink()
{
    linkN--;
}



// 获取大小
void FileOpenList::clear()
{
    for(int i = 0; i < MAX_FDS; i++)
    {
        if(fileOpenList[i].getLink() > 0)
            fileOpenList[i].clear();
    }
    fileOpenSize = 0;
}

// 删除引用
bool FileOpenList::deleteLink(int id)
{
    if(fileOpenList[id].getLink() <= 0)
        return false;
    fileOpenList[id].dcrLink();
    if(fileOpenList[id].getLink() == 0)
        deleteItem(id);
    return true;
}

// 增加引用
bool FileOpenList::addLink(int id)
{
    if(fileOpenList[id].getLink() <= 0)
        return false;
    fileOpenList[id].icrLink();
    return true;
}

// 删除某一项
bool FileOpenList::deleteItem(int id)
{
    if(fileOpenList[id].getLink() <= 0)
        return false;
    fileOpenList[id].clear();
    fileOpenSize--;
    return true;
}

// 添加某一项
int FileOpenList::addItem(int offset, int flags, int mode, int id)
{
    int i = getFreeItem();
    if(i == -1)
        return -1;
    FileOpenItem t(offset, flags, mode, id);
    fileOpenList[i] = t;
    return i; // 返回系统文件打开表的下标
}

// 获取空闲块
int FileOpenList::getFreeItem()
{
    for(int i = 0; i < MAX_FDS; i++)
        if(fileOpenList[i].getLink() == 0)
            return i;
    return -1;
}

// 获取某一项的inode编号
int FileOpenList::getItemINode(int id)
{
    if(fileOpenList[id].getLink() == 0)
        return -1;
    else
        return fileOpenList[id].getId();
}


UserOpenItem(){}

UserOpenItem::UserOpenItem(int descriptor, int id)
: descriptor(descriptor)
, id(id){}
// 清空
void UserOpenItem::clear()
{
    descriptor = id = -1;
}
// 设置值
void UserOpenItem::set(int descriptor, int id)
{
    this->descriptor = descriptor;
    this->id = id;
}
// 获取描述符
int UserOpenItem::getDescriptor()
{
    return descriptor;
}
// 获取id
int UserOpenItem::getId()
{
    return id;
}
// 检查是否可用
bool UserOpenItem::check()
{
    if(descriptor < 0)
        return false;
    return true
}