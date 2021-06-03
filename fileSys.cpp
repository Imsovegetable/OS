//
// Created by 旧城筱雨 on 2021/5/28.
//

#include "fileSys.h"


fileSystem fileSys;

SuperBlock::SuperBlock() {superGroup.init();}
// 创建文件
bool SuperBlock::createFile(const string& fileName, Directory* cur_dir)
{
    //为新建的文件开辟一个空闲的i结点
    int i = iNodeList.getFreeInodeNum();
    if(i == -1)
    {
        cout << "I-nodes have been run out\n";
        return false;
    }
    //为当前的目录的map添加文件的键值对
    cur_dir->addItem(fileName, i);
    //更新对应i结点的位示图
    iNodeDistributeList[i] = true;
    //
    int id = cur_dir->getItem(".");
    int n = iNodeList.getInode(id).differ();
    iNodeList.getInode(id).updateFileSize();
    while(n > 0)
    {
//        cout << superGroup.size() << endl;
        int bid = superGroup.getFreeBlock();
        if(bid == -1)
        {
            cout << "block has been run out\n";
            return false;
        }
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
    else
        return false;
    return true;
}

//创建文件
void fileSystem::fileCreate(const string& fileName)
{
    //遍历current_dir的所有指向的文件的i结点，查找是否已经有当前这个文件名了,如果有输出错误
    Directory* cur_dir = users.getCurDir();
    if(cur_dir != nullptr)
    {
        if(cur_dir->checkItem(fileName))
        {
            cout << "the file '" << fileName << "' has already existed\n";
            return ;
        }
        if(superBlock.createFile(fileName, cur_dir))
        {
            openFile(fileName, 0, 1);
            cout << "create successfully\n";
        }
    }
    else
        cout << "you are not authenticated!\n";
}


//在超级块中相关的删除文件函数
void SuperBlock::deleteFile(const string &fileName, Directory& directory) {
    int pos = -1;
    //当前的目录是current_dir,需要在current_dir下面获取文件名所对应外存里存的i结点编号
    pos = directory.getItem(fileName);
    if (pos == -1)
    {
        cout << "the file does not exist!" << endl;
        return;
    }
    //在当前的目录下删除对应文件的键值对
    directory.deleteItem(fileName);
    //删除对应的位示图
    iNodeDistributeList[pos] = false;
    //删除外存i结点表里面的i结点
    iNodeList.FreeInvalidInode(pos);
    //对超级块中记录的外存的i结点空闲结点数更新
    free_inode++;
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
    Directory* t = users.getCurDir();
    if(t == nullptr)
    {
        cout << "you are not authenticated!\n";
        return;
    }
    int pos = -1;
    pos = t->getItem(fileName);
    if(pos == -1)
    {
        cout << "file does not exist!\n";
        return;
    }
    int num = userOpenList[current_user].count(pos);
    while(num > 0)
    {
        closeFileForDelete(fileName);
        num--;
    }
    //pos是对应文件在外存中的i结点表中的位置
//    int tmp = iNodeListInRam.searchNode(pos);
//    if(tmp == -1){
//        cout << "the file does not exist in iNodeListRam" << endl;
//        return;
//    }
    //检查当前用户是否有该文件的创建和删除的权限
    if(superBlock.iNodeList.getInode(pos).inodeIsAuthor(current_user)){
//        //在内存i结点表中删除对应位置的i结点
//        iNodeListInRam.freeNode(tmp);
        //在超级块中对外存的i结点表中对应的i结点进行删除
        superBlock.deleteFile(fileName, *users.getCurDir());
    }
    else
    {
        cout << "you are not authenticated!\n";
    }
}

//超级块的删除目录函数
void SuperBlock::deleteDirectory(const string& directoryName, INode& dir, Directory& directory, int pos) {
    /*
     * 在超级块中删除对应目录的函数主要包括删除对应i结点的位示图中的位置，在当前目录下删除要删除目录的键值对，在外存的i结点表中删除对应的i结点
     * */
    //位示图对应的点置为false
    iNodeList.iNodeSize--;
    iNodeDistributeList[pos] = false;
    //在当前的目录的map键值对下删除对应的键值对
    directory.deleteItem(directoryName);
    //在外存i结点表删除对应的i结点
    iNodeList.FreeInvalidInode(pos);
}

//超级块中创建目录的函数
void SuperBlock::createDirectory(const string &directoryName, INode &dir, Directory* directory, int pos) {
    /*
     * 在超级块中创建目录函数需要更新当前目录的map,更新外存i节点表,以及更新位示图
     * */
    iNodeList.iNodeSize++;
    // 更新i结点位示图
    iNodeDistributeList[pos] = true;
    // 更新外存的i结点表
    iNodeList.inodeList[pos] = dir;
    // 更新键值对
    directory->addItem(directoryName, pos);
//    cout << directory->getItem("..")<< endl;

}

// 创建文件和目录的总体函数
void SuperBlock::createFileAndDirectory() {

}

// 删除文件和目录的总体函数
void SuperBlock::deleteFileAndDirectory() {

}

//文件系统中的保存所有i结点信息的函数
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
     * 在外存的i结点表里进行存储位示图和i结点表，另外再把新生成的目录写到当前目录的map中
     * */
    //parent_id表示上层目录文件夹i结点的id
    int parent_id;
    Directory* t = users.getCurDir();
    if(t == nullptr)
    {
        cout << "you are not authenticated!\n";
        return;
    }
    parent_id =t->getItem(".");
    //获取空闲的i结点
    int pos = superBlock.iNodeList.getFreeInodeNum();
    if(pos == -1)
    {
        cout << "the inodes has run out!" << endl;
        return ;
    }
    //cur_id表示当前目录i结点的id
    int cur_id = pos;
    INode newInode(1, getcurrentTime(), getcurrentTime(), current_user);
    //在directory进行init，设置当前目录的父目录和自身
    newInode.dir.init(cur_id, parent_id);
//    cout << cur_id << " " << parent_id << endl;
    //调用superBlock中的创建
    if(superBlock.iNodeList.getInode(parent_id).inodeIsAuthor(current_user)){
        //调用超级块superblock中的create函数
        superBlock.createDirectory(directoryName, newInode, users.getCurDir(), pos);
    }
    else
    {
        cout << "you are not authenticated!\n";
        return;
    }
    //cout << superBlock.iNodeList.getInode(cur_id).dir.getItem(".") << endl;
    users.setCurDir(&(superBlock.iNodeList.getInode(cur_id).dir));
}

//文件系统主类下面的删除目录函数
void fileSystem::directoryDelete(const string &directoryName) {
    /*
     * 在文件系统主类下删除目录函数主要包括：
     * 在外存的i结点表更新位示图对应的结点，更新i结点表删除对应i结点，另外再在当前的目录的map下删除需要删除的目录
     * */
    //pos存储对应目录i结点在外存i结点表的编号
    Directory* t = users.getCurDir();
    if(t == nullptr)
    {
        cout << "you are not authenticated!\n";
        return;
    }
    int pos = -1;
    pos = users.getCurDir()->getItem(directoryName);
    if(pos == -1){
        cout << "the directory does not exist!" << endl;
        return ;
    }
    if(superBlock.iNodeList.getInode(pos).inodeIsAuthor(current_user)){
        //获取i结点的函数：INode getInode(int id)
        INode tmp = superBlock.iNodeList.getInode(pos);
        superBlock.deleteDirectory(directoryName, tmp, *users.getCurDir(), pos);
    }


}

//文件系统下面的读取i结点到外存i结点表中的函数
void fileSystem::readInodeInfo() {

    //将所有txt中的信息读到i结点中作为记录，在每次用户登录之后都要进行函数调用来存储
    ifstream file("inodesInfo.txt");
    if(!file.is_open()){
        cout << "inodeInfo.txt can not open in readInodeInfo function" << endl;
        return ;
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
    if(dir == nullptr)
    {
        cout << "you are not authenticated!\n";
        return false;
    }
    // 获取要打开文件的inode下标
    int id = dir->getItem(fileName);
    // 不存在该文件
    if(id == -1)
        return false;
    if(superBlock.iNodeList.getInode(id).getType() == 1)
    {
        cd(fileName);
        return true;
    }
    // 获取要打开文件的内存i结点表下标
    int id_ram = iNodeListInRam.searchNode(id);
    // 该i结点未存入内存i节点表
    if(id_ram == -1)
    {
        // 载入该i结点，若载入失败说明内存i节点表已满
        if(!iNodeListInRam.loadNode(superBlock.iNodeList.getInode(id), id))
            return false;
    }
//    cout << current_user << endl;
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
    cout << "open successfully\n";
    return true;
}

// 关闭文件
bool fileSystem::closeFileForDelete(string fileName)
{
    // 获取当前目录
    Directory* dir = users.getCurDir();
    if(dir == nullptr)
    {
        cout << "you are not authenticated!\n";
        return false;
    }
    // 获取要关闭文件的inode下标
    int id = dir->getItem(fileName);
    if(id == -1)
        return false;
    // 获取该文件在系统打开表中的下标
    int id_sys_list = userOpenList[current_user].getFileId(id);
    // 在用户打开表中删除这一项
    userOpenList[current_user].deleteItem(id);
    // 在系统文件打开表中删除引用，如果引用项只有一个，则删除该项
    bool sign1 = fileOpenList.deleteLink(id_sys_list);
    bool sign;
    if(sign1)
    {
        // 如果引用项只有一个，则删除该项后还需要删除内存i结点表的引用
        sign = iNodeListInRam.getNode(id).delLink();
        if (sign)
        {
            // 如果内存i结点表的引用只有这一个，则释放该结点
            INode t = iNodeListInRam.freeNode(id);
            superBlock.iNodeList.UpdateInode(id, t);
        }
    }
    return true;
}

// 关闭文件
bool fileSystem::closeFile(string fileName)
{
    // 获取当前目录
    Directory* dir = users.getCurDir();
    if(dir == nullptr)
    {
        cout << "you are not authenticated!\n";
        return false;
    }
    // 获取要关闭文件的inode下标
    int id = dir->getItem(fileName);
    if(id == -1)
        return false;
    int num = userOpenList[current_user].count(id);
    if(num > 1)
    {
        cout << "choose a process to continue[1-" << num <<"]:";
        int n;
        cin >> n;
        if(n > num || n < 1)
            num = 1;
        num = n ;
    }
    // 获取该文件在系统打开表中的下标
    int id_sys_list = userOpenList[current_user].getFileId(id, num);
    // 在用户打开表中删除这一项
    userOpenList[current_user].deleteItem(id);
    // 在系统文件打开表中删除引用，如果引用项只有一个，则删除该项
    bool sign1 = fileOpenList.deleteLink(id_sys_list);
    bool sign;
    if(sign1)
    {
        // 如果引用项只有一个，则删除该项后还需要删除内存i结点表的引用
        sign = iNodeListInRam.getNode(id).delLink();
        if (sign)
        {
            // 如果内存i结点表的引用只有这一个，则释放该结点
            INode t = iNodeListInRam.freeNode(id);
            superBlock.iNodeList.UpdateInode(id, t);
        }
    }
    cout << "close successfully\n";
    return true;
}

void fileSystem::showDir()
{
    Directory* curDir = users.getCurDir();
    if(curDir == nullptr)
    {
        cout << "you are not authenticated!\n";
        return;
    }
    for(int i=0; i<curDir->size(); i++){
        string fileName = curDir->getFileName(i);
        int inodeId = curDir->getItem(fileName);
        cout << fileName << "   " << superBlock.iNodeList.inodeList[inodeId].getUser() << "   ";
        if(superBlock.iNodeList.inodeList[inodeId].getType() == 1)
        {
            cout << "file" << "   " << endl;
        }
        else{
            cout << "directory" << "   " << endl;
        }
    }
}
void fileSystem::fileRename(string &fileName, string &newName)
{
    Directory* curDir = users.getCurDir();
    if(curDir == nullptr)
    {
        cout << "you are not authenticated!\n";
        return;
    }
    int pos = curDir->getItem(fileName);
    if(pos == -1)
    {
        cout << "the file does not exists!\n";
        return;
    }
    curDir->setFileName(fileName, newName);
}


void fileSystem::copy(string fileName)
{
    Directory* dir = users.getCurDir();
    if(dir == nullptr)
    {
        cout << "you are not authenticated!\n";
        return;
    }
    int id = dir->getItem(fileName);
    if(id == -1)
    {
        cout << "file does not exists!\n";
        return;
    }
    INode t = iNodeListInRam.getNode(id);
    cacheFilename = fileName;
    cache = t;
}

void fileSystem::paste()
{
    Directory* dir = users.getCurDir();
    if(dir == nullptr)
    {
        cout << "you are not authenticated!\n";
        return;
    }
    if(dir->checkItem(cacheFilename))
    {
        cout << "the file '" << cacheFilename << "' has already existed\n";
        return ;
    }

    //为粘贴的文件开辟一个空闲的i结点
    int i = superBlock.iNodeList.getFreeInodeNum();
    if(i == -1)
    {
        cout << "I-nodes have been run out\n";
        return;
    }
    //为当前的目录的map添加文件的键值对
    dir->addItem(cacheFilename, i);
    //更新对应i结点的位示图
    iNodeDistributeList[i] = true;
    //
    int id = dir->getItem(".");
    int n = superBlock.iNodeList.getInode(id).differ();
    superBlock.iNodeList.getInode(id).updateFileSize();
    while(n > 0)
    {
        int bid = superBlock.superGroup.getFreeBlock();
        if(bid == -1)
        {
            cout << "block has been run out\n";
            return;
        }
        superBlock.iNodeList.getInode(id).addBlock(bid);
        n--;
    }
    // 回收多余的块
    while(n < 0)
    {
        int bid = superBlock.iNodeList.getInode(id).freeBlock();
        superBlock.superGroup.addNewBlock(bid);
        n++;
    }
    //写入内存表中
    if(superBlock.iNodeList.addNewINode(cache, i))
    {
        superBlock.free_inode--;
    }
//    cout << cache.content << endl;
    openFile(cacheFilename, 0, 1);
    cout << "paste successfully\n";
}


// 读取文件
string fileSystem::readFile(string fileName, int len)
{
    // 获取当前目录
    Directory* dir = users.getCurDir();
    if(dir == nullptr)
    {
        cout << "you are not authenticated!\n";
        return "";
    }
    // 获取要读取文件的inode下标
    int id = dir->getItem(fileName);
    if(id == -1)
        return "";
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
        cout << "choose a process to continue[1-" << num <<"]:";
        int n;
        cin >> n;
        if(n > num || n < 1)
            num = 1;
        num = n ;
    }
    // 获取该文件在系统文件打开表的下标
    int id_sys_list = userOpenList[current_user].getFileId(id, num);
    if(id_sys_list == -1)
        return "";
    // 获取当前偏移量
    int offset = fileOpenList.getOffset(id_sys_list);
//    cout << offset << endl;
    // 如果偏移量超过文件长度
    if(offset + len > iNodeListInRam.getNode(id).content.size())
        len = iNodeListInRam.getNode(id).content.size() - offset;
    // 设置读取后的偏移量
    fileOpenList.setOffset(id_sys_list, offset + len);
    // 输出读取的内容
    string out = iNodeListInRam.getNode(id).content.substr(offset, len);
    return out;
}

// 写入文件
bool fileSystem::writeFile(string fileName, string content)
{
    // 获取当前目录
    Directory* dir = users.getCurDir();
    if(dir == nullptr)
    {
        cout << "you are not authenticated!\n";
        return false;
    }
    // 获取要读取文件的inode下标
    int id = dir->getItem(fileName);
    if(id == -1)
        return false;
    //验证权限
    if(superBlock.iNodeList.getInode(id).getUser() != current_user)
    {
        cout << "you are not authenticated!\n";
        return "";
    }
    int num = userOpenList[current_user].count(id);
    if(num > 1)
    {
        cout << "choose a process to continue[1-" << num <<"]:";
        int n;
        cin >> n;
        if(n > num || n < 1)
            num = 1;
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
    // 更新偏移量
    fileOpenList.setOffset(id_sys_list, offset + content.size());
    // 拼接写入后的字符串
    string in1 = iNodeListInRam.getNode(id).content.substr(0, offset);
    string in2 = iNodeListInRam.getNode(id).content.substr(offset, iNodeListInRam.getNode(id).content.size() - offset);
    string out = in1 + content + in2;
    iNodeListInRam.getNode(id).content = out;
    // 计算大小变化
    int n = sizeof(out) - iNodeListInRam.getNode(id).size();
    // 分配新的块
    while(n > 0)
    {
        int bid = superBlock.superGroup.getFreeBlock();
        if(bid == -1)
        {
            cout << "block has been run out\n";
            return false;
        }
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

// 返回目录上一级
Directory* fileSystem::returnToParent()
{
    Directory* t = users.getCurDir();
    int id = t->getItem("..");
    t = &(superBlock.iNodeList.getInode(id).dir);
    users.setCurDir(t);
    return t;
}

//创建根目录的函数
void fileSystem::createRootDirectory() {
    /*
     *根目录的创建不需要找到对应的父母i结点的id,分配在外存i结点表的第0号结点位置
     * */
    superBlock.iNodeList.iNodeSize++;
    iNodeDistributeList[0] = true;
    INode RootInode(1, getcurrentTime(), getcurrentTime(), current_user);
    RootInode.dir.init(0, 0);
    superBlock.iNodeList.inodeList[0] = RootInode;
}

//创建用户目录
int fileSystem::createUserDirectory(string username)
{
    int parent_id = 0;
    //获取空闲的i结点
    int pos = superBlock.iNodeList.getFreeInodeNum();
    if(pos == -1){
        cout << "the inodes has run out!" << endl;
        return -1;
    }
    //cur_id表示当前目录i结点的id
    int cur_id = pos;
    //判断当前用户是否有创建和删除目录的权限
    INode newInode(1, getcurrentTime(), getcurrentTime(), username);
    //在directory进行init，设置当前目录的父目录和自身
    newInode.dir.init(cur_id, parent_id);

    superBlock.iNodeList.iNodeSize++;
    // 更新i结点位示图
    iNodeDistributeList[pos] = true;
    // 更新外存的i结点表
    superBlock.iNodeList.inodeList[pos] = newInode;
    // 更新键值对
    superBlock.iNodeList.getInode(0).dir.addItem(username, pos);

    return pos;
}
// 初始化
void fileSystem::init()
{
    createRootDirectory();
    users.createUser("user", "user");
    users.createUser("sakura", "sakura");
    int i = createUserDirectory("user");
    int j = createUserDirectory("sakura");
    users.userList[0].setCurDir(&(superBlock.iNodeList.getInode(i).dir));
    users.userList[1].setCurDir(&(superBlock.iNodeList.getInode(j).dir));
}
// 输出文件路径

void fileSystem::cd(string directoryName)
{
    Directory* t = users.getCurDir();
    if(t == nullptr)
    {
        cout << "you are not authenticated!\n";
        return;
    }
    int id = t->getItem(directoryName);
    if(id == -1)
    {
        cout << "no such directory\n";
        return;
    }
    users.setCurDir(&(superBlock.iNodeList.getInode(id).dir));
}

//文件系统格式化
void fileSystem::formatFileSystem() {
    /*
     * 文件系统的格式化包括，重置外存保存用户，重置外存i结点表，重置内存i结点表
     * */
    superBlock.iNodeList.iNodeSize = 0;
    current_user = "";
    //重置位示图
    for(bool & i : iNodeDistributeList){
        i = false;
    }
    //重置外存i结点表
    for(int i=0; i<superBlock.iNodeList.inodeList->size(); i++){
        superBlock.iNodeList.inodeList[i].freeBlock();
    }
    //重置用户表
    for(auto & i : users.userList){
        i.clear();
    }
    //重置内存i结点表
    for(int i=0; i<users.userList.size(); i++){
        iNodeListInRam.freeNode(i);
    }
}


