//
// Created by 旧城筱雨 on 2021/5/28.
//

#include "inode.h"
using namespace std;

//模拟i结点的位示图，用来分配的时候查看i结点的空闲情况
bool iNodeDistributeList[INODE_NUM];

INode::INode(){}
//复制构造函数，方便将i节点表copy到内存的i结点表中
INode::INode(const INode &A)
{
    type = A.type;
    dir = A.dir;
    fileLen = A.fileLen;
    diskSize = A.diskSize;
    setTime = A.setTime;
    username = A.username;
    updateTime = A.updateTime;
    i_Nlink = A.i_Nlink;
    content = A.content;
    indexT = A.indexT;
}
// 赋值构造函数
INode::INode(int type, string setTime, string updateTime, string username, int fileLen, int diskSize, int i_Nlink, string content)
        : type(type)
        , setTime(setTime)
        , updateTime(updateTime)
        , username(username)
        , fileLen(fileLen)
        , diskSize(diskSize)
        , i_Nlink(i_Nlink)
        , content(content)
{

}
//重载等号运算符，返回一个引用对象
INode& INode::operator=(const INode& B)
{
    this->dir = B.dir;
    this->updateTime = B.updateTime;
    this->setTime = B.setTime;
    this->diskSize = B.diskSize;
    this->fileLen = B.fileLen;
    this->username = B.username;
    this->i_Nlink = B.i_Nlink;
    this->content = B.content;
    this->indexT = B.indexT;
    return *this;
}
//更新i结点的相关信息
void INode::updateFileSize()
{
    if(type == 1)
        fileLen = sizeof(dir);
    else
        fileLen = content.size();
}
// 返回文件大小
int INode::size() const
{
    return fileLen;
}
// 返回文件变化情况
int INode::differ()
{
    int t;
    if(type == 1)
        t = sizeof(dir) - fileLen;
    else
        t = content.size() - fileLen;
    fileLen = t;
    return t;
}
// 移除一个块
int INode::freeBlock()
{
    return indexT.dropIndex();
}
// 添加一个块
bool INode::addBlock(int id)
{
    return (indexT.addIndex(id)) ? (diskSize++, true):(false);
}
// 获取块数
int INode::num()
{
    return diskSize;
}
// 获取用户名
string INode::getUser()
{
    return username;
}
// 清空inode
void INode::clear()
{
    type = -1;
    dir.clear();
    fileLen = 0;
    diskSize = 0;
//        setTime = ;
    username = "";
    i_Nlink = 0;
    content = "";
    indexT.clear();
}
//更新i结点
void INodeList::UpdateInode(int id, INode ano)
{
    inodeList[id] = ano;
}
//计算i结点对应文件内容的大小
int INode::calculateFileSize(const string& filename)
{
    ifstream file(filename);
    if(!file.is_open())
        return -1;
    string t;
    file >> noskipws >> t;
    return t.size();
}
//获取硬连接数
int INode::check()
{
    return i_Nlink;
}
// 获取i节点表的空闲项编号
int INodeList::getFreeInodeNum()
{
    for(int i=0; i<INODE_NUM; i++)
    {
        if(!iNodeDistributeList[i])
            return i;
    }
    return -1;
}
// 添加新的i结点
bool INodeList::addNewINode(INode A, int i) {
    inodeList[i] = A;
    iNodeSize++;
    return true;
}


void INodeList::FreeInvalidInode(int pos) {
    iNodeDistributeList[pos] = false;
    inodeList[pos].clear();
    iNodeSize--;
}

INode& INodeList::getInode(int id)
{
    return inodeList[id];
}

string INode::save_as_string() {
    string ans;
    ans = username + '\n' + to_string(type) + '\n' + to_string(i_Nlink) + '\n' + to_string(fileLen) + '\n'
            + to_string(diskSize) + '\n' + setTime + updateTime + '\n';
    ans +=  (to_string(dir.size()) + '\n');
    vector<int> tmp = indexT.getIndexes();
    for(int i : tmp){
        ans += ans + to_string(i);
        ans += '\n';
    }
    return ans;
}

int INode::getType() {
    return type;
}

void INode::addLink()
{
    i_Nlink++;
}

bool INode::delLink()
{
    i_Nlink--;
    if(i_Nlink == 0)
        return true;
    else
        return false;
}

void INode::saveDiskNumber(const vector<int>& numberSet) {
    for(int i : numberSet){
        indexT.addIndex(i);
    }
}

bool INode::inodeIsAuthor(string username) {
    if(getUser() == username)
        return true;
    return false;
}


