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

void fileSystem::saveInodeInfo() {
    //将所有i结点的信息写到txt中作为记录，在每次用户退出登录之后要进行函数调用来存储
    ofstream file("inodesInfo.txt");
    if(!file.is_open()){
        cout<<"inodesInfo.txt can not open in saveInodeInfo function "<<endl;
        exit(0);
    }
    //首先存储位示图，根据位示图的值来判断是否有对应的i结点
    for(int i=0; i<INODE_NUM; i++){
        file<<iNodeDistributeList[i]<<endl;
    }
    for(int i=0; i<INODE_NUM; i++){
        //如果位示图的是true，代表i结点存在
        if(iNodeDistributeList[i]){
            //存储i结点的一些公共属性
            file<<superBlock.iNodeList.inodeList[i].username<<endl;
            file<<superBlock.iNodeList.inodeList[i].type<<endl;
            file<<superBlock.iNodeList.inodeList[i].i_Nlink<<endl;
            file<<superBlock.iNodeList.inodeList[i].fileLen<<endl;
            file<<superBlock.iNodeList.inodeList[i].diskSize<<endl;
            file<<superBlock.iNodeList.inodeList[i].setTime<<endl;
            file<<superBlock.iNodeList.inodeList[i].updateTime<<endl;
            //存储i结点的索引块的编号
            file<<superBlock.iNodeList.inodeList[i].indexT.getIndexes()<<endl;
            if(superBlock.iNodeList.inodeList[i].type == 1){
                //如果i结点是目录类型
                //如果是目录需要存储对应的目录下面的文件标识
                file<<superBlock.iNodeList.inodeList[i].dir.getFileNumFromDir()<<endl;
                map<string, int>::iterator iter;
                for(iter = superBlock.iNodeList.inodeList[i].directory.begin(); iter != superBlock.iNodeList.inodeList[i].directory.begin().end(); iter++){
                    file<<iter->first<<endl;
                    file<<iter->second<<endl;
                }
            }
            else if(superBlock.iNodeList.inodeList[i].type == 0) {
                //如果i结点是文件类型
                //如果是文件类型，需要存储对应的文本内容
                file << superBlock.iNodeList.inodeList[i].content << endl;
            }
        }
    }
    file.close();
}

void fileSystem::readInodeInfo() {
    //将所有txt中的信息读到i结点中作为记录，在每次用户登录之后都要进行函数调用来存储
    ifstream file("inodesInfo.txt");
    if(!file.is_open()){
        cout<<"inodeInfo.txt can not open in readInodeInfo function"<<endl;
        exit(0);
    }
    string line;
    //读取位示图
    for(int i=0; i<INODE_NUM; i++){
        file>>line;
        if(line == "1")
            iNodeDistributeList[i] = true;
        else
            iNodeDistributeList[i] = false;
    }
    for(int i=0; i<INODE_NUM; i++){
        if(iNodeDistributeList[i]){
            //如果位示图对应结点值为true，此时可以进行读取结点信息
            file >> superBlock.iNodeList.inodeList[i].username;
            file >> superBlock.iNodeList.inodeList[i].type;
            file >> superBlock.iNodeList.inodeList[i].i_Nlink;
            file >> superBlock.iNodeList.inodeList[i].fileLen;
            file >> superBlock.iNodeList.inodeList[i].diskSize;
            file >> superBlock.iNodeList.inodeList[i].setTime;
            file >> superBlock.iNodeList.inodeList[i].updateTime;
            file >> line;
            int s = 0;
            //记录每个文件/目录对应的索引块，首先读入一个字符串，然后对字符串中处理成对应的数字存储到i结点的索引数组中
            for(int i=0; i<line.size(); i++){
                if(s[i] >= '0' && s[i] <= '9'){
                    s = s*10 + s[i] - '0';
                }
                else if(s[i])
                    superBlock.iNodeList.inodeList[i].indexT.indexes.push_back(s), s=0;
            }
            if(superBlock.iNodeList.inodeList[i].type == 1){
                //i结点对应的type值为1代表i结点存储的是目录类型
                file >> line;
                int s = 0;
                for(int i=0; i<line.size(); i++){
                    s = s*10 + line[i]-'0';
                }
                while(s--){
                    string key;
                    string value;
                    int val;
                    line>>key;
                    line>>val;
                    val = atoi(value.c_str());
                    superBlock.iNodeList.inodeList[i].dir.addItem(key, val);
                }
            }
            else if(superBlock.iNodeList.inodeList[i].type == 0){
                //如果i结点的type值为0代表i结点存储的是文件类型，需要存储对应的文本内容
                file >> superBlock.iNodeList.inodeList[i].content;
            }
        }

    }

}