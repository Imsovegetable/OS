//
// Created by Chen Yining on 2021/5/27.
//

#ifndef OS_FILESYSTEM_H
#define OS_FILESYSTEM_H
#include "INode.h"
#include "GODNING.h"
#include "memory.h"
//#include "user.cpp"

class SuperBlock{
public:
    int inodeNum = InodeNum;        //总共的i结点数
    int free_inode;                 //空闲i结点数量

    int disk;                       //磁盘块总个数
    int free_disk;                  //空闲磁盘块总个数

    INodeList iNodeList;
    //其他待补充！！！
    //为创建文件分配一个i结点
    int distributeInode();

};


int SuperBlock::distributeInode() {
    if(free_inode == 0){
        cout<<"无空闲i结点块可供分配"<<endl;
        return -1;
    }
    int pos = iNodeList.getFreeInodeNum();
    return pos;
}

class fileSystem{
public:
    //超级块
    static SuperBlock superBlock;
    //创建文件
    static void fileCreate(const string& fileName);


};

void fileSystem::fileCreate(const string& fileName) {
    //遍历current_dir的所有指向的文件的i结点，查找是否已经有当前这个文件名了,如果有输出错误
    //如果文件名不存在
    //为新建的文件开辟一个空闲的i结点
    int posNum = superBlock.distributeInode();
    //current_dir->dir.insert({filename, posNum});
    //写入内存表中


}

#endif //OS_FILESYSTEM_H
