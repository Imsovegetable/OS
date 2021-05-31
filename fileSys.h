//
// Created by 旧城筱雨 on 2021/5/28.
//
#include "directory.h"
#include "inode.h"
#include "GODNING.h"
#include "memory.h"
#include "user.h"
#include "help.h"
#include "ram.h"

#ifndef OS_FILESYS_H
#define OS_FILESYS_H

//
// Created by Chen Yining on 2021/5/27.
//

class SuperBlock{
public:
    int inodeNum = INODE_NUM;        //总共的i结点数
    int free_inode = INODE_NUM;          //空闲i结点数量

    int disk = TOTAL_GROUP_SIZE;                       //磁盘块总个数
    int free_disk = TOTAL_GROUP_SIZE;                  //空闲磁盘块总个数

    INodeList iNodeList;
    //其他待补充！！！
    //为创建文件分配一个i结点
    //在超级块中的相关创建文件函数
    void createFile(const string& fileName, INode& A);
    //在超级块中的相关删除文件函数
    void deleteFile(const string& fileName);

};

class fileSystem{
public:
    //超级块
    SuperBlock superBlock;
    //内存i结点表
    INodeListInRam iNodeListInRam;
    //创建文件
    void fileCreate(const string& fileName);
    //删除文件
    void fileDelete(const string& fileName);
    //创建目录
    void directoryCreate(const string& directoryName);
    //删除目录
    void directoryDelete(const string& directoryName);
    //保存所有i结点，在用户退出的时候调用以保存所有的i结点信息
    void saveInodeInfo();
    //读取所有i结点的信息，在用户登录之后调用以读取所以的i结点信息
    void readInodeInfo();
};



#endif //OS_FILESYS_H
