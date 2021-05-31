//
// Created by 旧城筱雨 on 2021/5/28.
//

#include "fileSys.h"

SuperBlock::SuperBlock() {superGroup.init();}
// 创建文件
void SuperBlock::createFile(const string& fileName, Directory* cur_dir)
{
    //为新建的文件开辟一个空闲的i结点
    int i = iNodeList.getFreeInodeNum();
    if(i == -1)
    {
        cout << "I-nodes have been run out\n";
        return;
    }
    //为当前的目录的map添加文件的键值对
    cur_dir->addItem(fileName, i);
    int id = cur_dir->getItem(".");
    int n = iNodeList.getInode(id).differ();
    iNodeList.getInode(id).updateFileSize();
    while(n > 0)
    {
        int bid = superGroup.getFreeBlock();
        iNodeList.getInode(id).addBlock(bid);
        n--;
    }
    // 回收多余的块
    while(n < 0)
    {
        int bid = iNodeList.getInode(id).freeBlock();
        superGroup.addNewBlock(bid);
        n++;
    }
    //写入内存表中
    INode newInode(0, getcurrentTime(), getcurrentTime(), current_user);
    if(iNodeList.addNewINode(newInode, i))
    {
        free_inode--;
    }
}

/*
 *
 *
********************************************************************************************************************
 *
 *
*/


//创建文件
void fileSystem::fileCreate(const string& fileName)
{
    //遍历current_dir的所有指向的文件的i结点，查找是否已经有当前这个文件名了,如果有输出错误
    Directory* cur_dir = users.getCurDir();
    if(cur_dir != nullptr)
    if(cur_dir->checkItem(fileName))
    {
        cout << "the file '" << fileName << "' has already existed\n";
        return ;
    }
    superBlock.createFile(fileName, cur_dir);
}

// 存储i结点信息
void fileSystem::saveInodeInfo()
{
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

//读取i结点信息
void fileSystem::readInodeInfo()
{
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

// 打开文件, sign = 0表示从头读取，sign = 1表示追加, mode = 0表示读, mode = 1表示写
bool fileSystem::openFile(string fileName, int sign, int mode)
{
    // 获取当前目录
    Directory* dir = users.getCurDir();
    // 获取要打开文件的inode下标
    int id = dir->getItem(fileName);
    // 不存在该文件
    if(id == -1)
        return false;
    // 获取要打开文件的内存i结点表下标
    int id_ram = iNodeListInRam.searchNode(id);
    // 该i结点未存入内存i节点表
    if(id_ram == -1)
    {
        // 载入该i结点，若载入失败说明内存i节点表已满
        if(!iNodeListInRam.loadNode(superBlock.iNodeList.getInode(id), id))
            return false;
    }
    if(userOpenList[current_user].getFileId(id) != -1)
    {
        cout << "do you want to open it separately? [Y/N]:";
        char c;
        cin >> c;
        if(!(c == 'Y' || c == 'y')) // N0
        {
            int id_sys_list = userOpenList[current_user].getFileId(id);
            if(!userOpenList[current_user].addItem(id, id_sys_list))
            {
                return false;
            }
            return true;
        }
    }
    // 该i结点增加链接
    iNodeListInRam.getNode(id).addLink();
    int id_sys_list;
    // 如果要以追加模式打开
    if(sign == 1)
        id_sys_list = fileOpenList.addItem(iNodeListInRam.getNode(id).size(), 0, mode, id);
    else  // 从头开始读
        id_sys_list = fileOpenList.addItem(0, 0, mode, id);
    // 添加到系统文件打开表
    if(userOpenList[current_user].getUserName() == "")
    {
        UserOpenList t1(current_user);
        userOpenList[current_user] = t1;
    }
    // 添加到用户文件打开表, 如果失败说明用户文件打开表已经满了
    if(!userOpenList[current_user].addItem(id, id_sys_list))
    {
        return false;
    }
    return true;
}

// 关闭文件
//bool fileSystem::closeFile(string fileName)
//{
//    // 获取当前目录
//    Directory* dir = users.getCurDir();
//    // 获取要关闭文件的inode下标
//    int id = dir->getItem(fileName);
//    if(id == -1)
//        return false;
//    // 获取该文件在系统打开表中的下标
//    int id_sys_list = userOpenList[current_user].getFileId(id);
//    // 在用户打开表中删除这一项
//    userOpenList[current_user].deleteItem(id);
//    // 在系统文件打开表中删除引用，如果引用项只有一个，则删除该项
//    bool sign1 = fileOpenList.deleteLink(id_sys_list);
//    bool sign;
//    if(sign1)
//    {
//        // 如果引用项只有一个，则删除该项后还需要删除内存i结点表的引用
//        sign = iNodeListInRam.getNode(id).delLink();
//        if (sign)
//        {
//            // 如果内存i结点表的引用只有这一个，则释放该结点
//            INode t = iNodeListInRam.freeNode(id);
//            superBlock.iNodeList.UpdateInode(id, t);
//        }
//    }
//    return true;
//}


// 读取文件
string fileSystem::readFile(string fileName, int len)
{
    // 获取当前目录
    Directory* dir = users.getCurDir();
    // 获取要读取文件的inode下标
    int id = dir->getItem(fileName);
    //验证权限
    if(superBlock.iNodeList.getInode(id).getUser() != current_user)
    {
        cout << "you are not authenticated!\n";
        return "";
    }
    // 统计该文件被打开了几次
    int num = userOpenList[current_user].count(id);
    if(num > 1)
    {
        // 选择一个进程以继续读操作
        cout << "choose 1 from " << num << " to continue:";
        int n;
        cin >> n;
        if(n > num || n < 1)
            return "";
        num = n;
    }
    // 获取该文件在系统文件打开表的下标
    int id_sys_list = userOpenList[current_user].getFileId(id, num);
    if(id_sys_list == -1)
        return "";
    // 获取当前偏移量
    int offset = fileOpenList.getOffset(id_sys_list);
    // 设置读取后的偏移量
    fileOpenList.setOffset(id, offset + len);
    // 输出读取的内容
    string out = iNodeListInRam.getNode(id).content.substr(offset, len);
    return out;
}

// 写入文件
bool fileSystem::writeFile(string fileName, string content)
{
    // 获取当前目录
    Directory* dir = users.getCurDir();
    // 获取要读取文件的inode下标
    int id = dir->getItem(fileName);
    //验证权限
    if(superBlock.iNodeList.getInode(id).getUser() != current_user)
    {
        cout << "you are not authenticated!\n";
        return "";
    }
    int num = userOpenList[current_user].count(id);
    if(num > 1)
    {
        cout << "choose 1 from " << num << " to continue:";
        int n;
        cin >> n;
        if(n > num || n < 1)
            return "";
        num = n;
    }
    // 获取系统文件打开表下标
    int id_sys_list = userOpenList[current_user].getFileId(id, num);
    if(id_sys_list == -1)
        return "";
    // 验证权限，是否可写
    if(fileOpenList.getMode(id_sys_list) == 0)
    {
        cout << "the file is read only!\n";
        return false;
    }
    // 获取文件偏移量
    int offset = fileOpenList.getOffset(id_sys_list);
    // 拼接写入后的字符串
    string in1 = iNodeListInRam.getNode(id).content.substr(0, offset);
    string in2 = iNodeListInRam.getNode(id).content.substr(offset, iNodeListInRam.getNode(id).content.size() - offset);
    string out = in1 + content + in2;
    iNodeListInRam.getNode(id).content = out;
    // 计算大小变化
    int n = out.size() - iNodeListInRam.getNode(id).size();
    // 分配新的块
    while(n > 0)
    {
        int bid = superBlock.superGroup.getFreeBlock();
        iNodeListInRam.getNode(id).addBlock(bid);
        n--;
    }
    // 回收多余的块
    while(n < 0)
    {
        int bid = iNodeListInRam.getNode(id).freeBlock();
        superBlock.superGroup.addNewBlock(bid);
        n++;
    }
    // 更新i结点里的容量信息
    iNodeListInRam.getNode(id).updateFileSize();
    return true;
}