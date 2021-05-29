//
// Created by 旧城筱雨 on 2021/5/28.
//

#include <bits/stdc++.h>
#include "GODNING.h"
#include "directory.h"
#include "memory.h"

#ifndef OS_INODE_H
#define OS_INODE_H

extern bool iNodeDistributeList[INODE_NUM];

class INode{
private:
    //存储i结点属于的用户名称
    string username = "";
    //表示i结点存储的类型，是文件还是目录，文件是0，目录是1
    int type = -1;
    // 硬连接数
    int i_Nlink = 0;
    //存储i结点对应的文件的文件长度(返回是一个字节数)
    int fileLen = 0;
    //存储i结点对应文件所占用的磁盘块数
    int diskSize = 0;
    //i结点对应文件/目录的创建时间
    string setTime = "";
    //i结点对应文件最近一次更新的时间
    string updateTime = "";
    // 指向混合索引表
    MixIndex indexT;

public:
    //每个i结点存一个目录索引，如果是文件则置空即可
    Directory dir;
    // 如果是普通文件话存储文件内容
    string content;

    INode();
    //复制构造函数，方便将i节点表copy到内存的i结点表中
    INode(const INode &A);
    // 赋值构造函数
    INode(int type, string setTime, string updateTime, string username);
    //重载等号运算符，返回一个引用对象
    INode &operator=(const INode& B);
    //更新i结点的相关信息
    void updateFileSize();
    // 返回文件大小
    int size() const;
    // 返回文件变化情况
    int differ();
    // 移除一个块
    bool freeBlock();
    // 添加一个块
    bool addBlock(int id);
    // 获取块数
    int num();
    // 获取用户名
    string getUser();
    // 清空inode
    void clear();
    // 获取硬连接数
    int check();
    //计算i结点对应文件内容的大小
    int calculateFileSize(const string& filename);
    //判断当前用户是否有打开i结点的权限
    bool inodeIsAuthor(string username);

};

//i结点表，存储在内存中
class INodeList{
private:
    // 已使用的i结点数量
    int iNodeSize = 0;
    //i结点表，在初次进入程序之后获取i结点表
    INode inodeList[INODE_NUM];
public:
    //获取空i结点号码
    int getFreeInodeNum();
    //添加新节点
    bool addNewINode(INode A, int i);
    //释放一个不用的i结点
    void FreeInvalidInode(int pos);
    //获取某个i结点的信息
    string getSpecificInodeInfo(int pos);
    //修改某个i结点的信息
    void UpdateInodeInfo(int pos);
    // 获取某个i结点
    INode getInode(int id);
};

#endif //OS_INODE_H
