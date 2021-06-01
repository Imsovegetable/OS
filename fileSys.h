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
#include "gcm.h"

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

    SuperGroup superGroup;
    //其他待补充！！！
    //为创建文件分配一个i结点


    SuperBlock();

    void createFile(const string& fileName, Directory* cur_dir);
    //在超级块中的相关删除文件函数
    void deleteFile(const string& fileName, Directory& directory);
    //超级块中创建目录函数
    void createDirectory(const string &directoryName, INode &dir, Directory* directory, int pos);
    //超级块中删除目录函数
    void deleteDirectory(const string& directoryName, INode& dir, Directory& directory, int pos);
    // 创建目录和文件的i结点的总体函数
    void createFileAndDirectory();
    // 删除目录和文件的总体函数
    void deleteFileAndDirectory();



};

class fileSystem{
public:
    //超级块
    SuperBlock superBlock;
    // 用户列表
    Users users;
    //文件系统内存i结点表
    INodeListInRam iNodeListInRam;

    FileOpenList fileOpenList;

    map<string, UserOpenList> userOpenList;
    //创建文件
    void fileCreate(const string& fileName);
    //保存所有i结点，在用户退出的时候调用以保存所有的i结点信息
    void saveInodeInfo();
    //读取所有i结点的信息，在用户登录之后调用以读取所以的i结点信息
    void readInodeInfo();

    // 打开文件
    bool openFile(string fileName, int sign = 0, int mode = 0); // sign = 0表示从头读取，sign = 1表示追加, mode = 0表示读, mode = 1表示写
    // 关闭文件，只能关闭当前目录下的文件
    bool closeFile(string fileName);
    // 读取文件
    string readFile(string fileName, int len);

    bool writeFile(string fileName, string content);

    void showFileInfo(string fileName);

    Directory* returnToParent();

    void directoryDelete(const string &directoryName);

    void directoryCreate(const string &directoryName);

    void fileDelete(const string &fileName);

    void createRootDirectory();

    int createUserDirectory(string username);

    void init();

    void cd(string filename);

    void formatFileSystem();
};

extern fileSystem fileSys;


//void fileSystem::showFileInfo(string fileName)
//{
//
//}

#endif //OS_FILESYS_H