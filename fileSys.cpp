//
// Created by 旧城筱雨 on 2021/5/28.
//

#include "fileSys.h"
#include "inode.h"

//超级块下面相关的创建文件函数
void SuperBlock::createFile(const string& fileName, INode &A)
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
    //更新对应i结点的位示图
    iNodeDistributeList[i] = true;
    //把新建的文件对应的i结点写入外存中的i结点表
    if(iNodeList.addNewINode(A, i))
    {
        free_inode--;
    }
}

//在超级块中相关的删除文件函数
void SuperBlock::deleteFile(const string &fileName) {
    int pos = -1;
    //当前的目录是current_dir,需要在current_dir下面获取文件名所对应外存里存的i结点编号
    pos = current_dir->getItem(fileName);
    if (pos == 0) {
        cout << "the file does not exist!" << endl;
        return;
    }
    //在当前的目录下删除对应文件的键值对
    current_dir->deleteItem(fileName);
    //删除对应的位示图
    iNodeDistributeList[pos] = false;
    //删除外存i结点表里面的i结点
    iNodeList.FreeInvalidInode(pos);
    //对超级块中记录的外存的i结点空闲结点数更新
    free_inode++;
}

//在fileSystem主类下的创建文件函数
void fileSystem::fileCreate(const string& fileName)
{
    //遍历current_dir的所有指向的文件的i结点，查找是否已经有当前这个文件名了,如果有输出错误
    if(current_dir->checkItem(fileName))
    {
        cout << "the file '" << fileName << "' has already existed\n";
        return ;
    }
    //新建对应的i结点的对象
    INode newInode(0, getcurrentTime(), getcurrentTime(), current_user->username);
    //获取内存i结点表中的空闲i结点编号
    int pos = iNodeListInRam.getFreeNode();
    //在内存中的内存i节点表中的添加对应的i结点
    //在内存i结点表添加i结点的函数：
    //bool loadNode(INode A, int id)
    iNodeListInRam.loadNode(newInode, pos);
    //在超级块中对外存i结点表创建对应的i结点
    superBlock.createFile(fileName, newInode);
}

//fileSystem主类下的删除文件函数
void fileSystem::fileDelete(const string &fileName) {
    /*
     * 文件系统中删除一个文件都包括以下几个方面：
     * 删除内存中内存i节点表中的i结点
     * 删除外存i结点表中的i结点
     * 将i结点位示图中的对应位置写成false
     * 为当前的目录的map删掉对应文件的键值对
     * */
    int pos = -1;
    //pos是对应文件在内存中的i结点表中的位置
    pos = current_dir->getItem(fileName);
    if(pos == 0){
        cout << "the file does not exist in iNodeListRam" << endl;
        return;
    }
    //在内存i结点表中删除对应位置的i结点
    iNodeListInRam.freeNode(pos);
    //在超级块中对外存的i结点表中对应的i结点进行删除
    superBlock.deleteFile(fileName);
}



void fileSystem::saveInodeInfo() {
    //将所有i结点的信息写到txt中作为记录，在每次用户退出登录之后要进行函数调用来存储
    ofstream file("inodesInfo.txt");
    if(!file.is_open()){
        cout<<"inodesInfo.txt can not open in saveInodeInfo function "<<endl;
        exit(0);
    }
    //首先存储位示图，根据位示图的值来判断是否有对应的i结点
    for(bool i : iNodeDistributeList){
        file<<i<<endl;
    }
    for(int i=0; i<INODE_NUM; i++){
        //如果位示图的是true，代表i结点存在
        if(iNodeDistributeList[i]){
            //存储i结点的一些公共属性以及索引编号
            file << superBlock.iNodeList.inodeList->save_as_string();
            if(superBlock.iNodeList.inodeList[i].getType() == 1){
                //如果i结点是目录类型
                //如果是目录需要存储对应的目录下面的文件标识
                file<<superBlock.iNodeList.inodeList[i].dir.getFileNumFromDir()<<endl;
                file<<superBlock.iNodeList.inodeList[i].dir.save_as_string_dir();
            }
            else if(superBlock.iNodeList.inodeList[i].getType() == 0) {
                //如果i结点是文件类型
                //如果是文件类型，需要存储对应的文本内容
                file << superBlock.iNodeList.inodeList[i].content << endl;
            }
        }
    }
    file.close();
}


//文件系统主类下面的创建目录函数
void fileSystem::directoryCreate(const string &directoryName) {
    /*
     * 在文件系统主类下创建目录函数主要包括：
     * 在cur_dir
     * */


}

//文件系统主类下面的删除目录函数
void fileSystem::directoryDelete(const string &directoryName) {

}

//文件系统下面的读取i结点到外存i结点表中的函数
void fileSystem::readInodeInfo() {
    //将所有txt中的信息读到i结点中作为记录，在每次用户登录之后都要进行函数调用来存储
    ifstream file("inodesInfo.txt");
    if(!file.is_open()){
        cout<<"inodeInfo.txt can not open in readInodeInfo function"<<endl;
        exit(0);
    }
    string line;
    //读取位示图
    for(bool & i : iNodeDistributeList){
        file>>line;
        if(line == "1")
            i = true;
        else
            i = false;
    }
    //根据位示图的存储情况进行判断，进而读取i结点的信息
    for(int i=0; i<INODE_NUM; i++){
        if(iNodeDistributeList[i]){
            string username, setTime, updateTime;
            int type, i_Nlink, fileLen, diskSize;
            //如果位示图对应结点值为true，此时可以进行读取结点信息
            file >> username;
            file >> type;
            file >> i_Nlink;
            file >> fileLen;
            file >> diskSize;
            file >> setTime;
            file >> updateTime;
            file >> line;
            //添加一个新的i结点
            INode A(type, setTime, updateTime, username, fileLen, diskSize, i_Nlink);
            superBlock.iNodeList.inodeList[i] = A;
            int dirSize = atoi(line.c_str());
            //这一行之前已经存储完了inode的所有基础元素
            //diskSet是暂时存储所有磁盘编号的数组
            vector<int> diskSet;
            while(dirSize--){
                //如果dirsize不是0，代表该文件/目录占磁盘块
                file >> line;
                int s = 0;
                //记录每个文件/目录对应的索引块，首先读入一个字符串，然后对字符串中处理成对应的数字存储到i结点的索引数组中
                for(char j : line){
                    if(j >= '0' && j <= '9'){
                        s = s*10 + j - '0';
                    }
                    else if(line[j])
                        //计算出对应inode存储的磁盘块的编号，然后写入索引表中
                        diskSet.push_back(s), s=0;
                }
            }
            //把diskSet存储到i结点对应的磁盘索引中
            superBlock.iNodeList.inodeList[i].saveDiskNumber(diskSet);

            if(type == 1){
                //i结点对应的type值为1代表i结点存储的是目录类型
                file >> line;
                //numFromDir获取目录对应的存储文件的文件数量
                int numFromDir = atoi(line.c_str());
                while(numFromDir--){
                    //按照计算出的文件数量进行获取文件的map索引
                    file >> line;
                    string key = line;
                    file >> line;
                    string value = line;
                    int val = atoi(value.c_str());
                    //存储对应的文件目录
                    superBlock.iNodeList.inodeList[i].dir.addItem(key, val);
                }
            }
            else if(type == 0){
                //如果i结点的type值为0代表i结点存储的是文件类型，则下一步是读取对应的文件内容
                file >> superBlock.iNodeList.inodeList[i].content;
            }
        }

    }

}




