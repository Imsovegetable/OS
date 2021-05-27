//
// Created by Chen Yining on 2021/5/27.
//

#ifndef OS_INODE_H
#define OS_INODE_H
#include "GODNING.h"

bool inodeDistributeList[InodeNum];      //模拟i结点的位示图，用来分配的时候查看i结点的空闲情况

class INode{
private:
    //每个i结点存一个目录索引，如果是文件则置空即可
    directory dir{};
    //存储i结点属于的用户名称
    string username;

public:
    //复制构造函数，方便将i节点表copy到内存的i结点表中
    INode(const INode &A){
        type = A.type;
        dir = A.dir;
        fileLen = A.fileLen;
        diskSize = A.diskSize;
        setTime = A.setTime;
        username = A.username;
        updateTime = A.updateTime;

    }
    //赋值构造函数
    INode(const string& username, int type, int fileLen, int diskSize, int setTime, int updateTime, directory dir){
        type = type;
        fileLen = fileLen;
        diskSize = diskSize;
        setTime = setTime;
        updateTime = updateTime;
        dir = dir;
    }
    //重载等号运算符，返回一个引用对象
    INode &operator=(const INode& B){
        this->dir = B.dir;
        this->updateTime = B.updateTime;
        this->setTime = B.setTime;
        this->diskSize = B.diskSize;
        this->fileLen = B.fileLen;
        this->username = B.username;
        this->txtFileName = B.txtFileName;
        return *this;
    }

    //表示i结点存储的类型，是文件还是目录，文件是0，目录是1
    int type{};
    //存储i结点对应的文件的文件长度(返回是一个字节数)
    int fileLen{};
    //存储i结点对应文件所占用的磁盘块数
    int diskSize{};
    //i结点对应文件/目录的创建时间
    string setTime;
    //i结点对应文件最近一次更新的时间
    string updateTime;
//    //更新i结点的相关信息
//    void UpdateInodeInfo();
    //存储真实存储的文本文件的文件名
    string txtFileName;
    //计算i结点对应文件内容的大小
    static int CaculateFileSize(const string& filename);

};

int INode::CaculateFileSize(const string& filename){
    ifstream file(filename);
    if(!file.is_open())
        return -1;
    string t;
    file >> noskipws >> t;
    return t.size();
}

//i结点表，存储在内存中
class INodeList{
public:
    //i结点表，在初次进入程序之后获取i结点表
    INode inodeList[InodeNum];
    //获取空i结点号码
    static int getFreeInodeNum();
    //释放一个不用的i结点
    void FreeInvalidInode(int pos);
    //获取某个i结点的信息
    void getSpecificInodeInfo(int pos);
    //修改某个i结点的信息
    void UpdateInodeInfo(int pos);

};

int INodeList::getFreeInodeNum() {
    for(int i=0; i<InodeNum; i++){
        if(inodeDistributeList[i] == false)
            return i;
    }
}

void INodeList::UpdateInodeInfo(int pos) {

}

void INodeList::FreeInvalidInode(int pos) {

}

void INodeList::getSpecificInodeInfo(int pos) {

}


#endif //OS_INODE_H
