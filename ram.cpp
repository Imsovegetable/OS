//
// Created by �ɳ����� on 2021/5/27.
//

#include "ram.h"

// ���캯��
INodeListInRam::INodeListInRam()
{
    for(int i = 0; i < INODET_IN_RAM; i++)
        iNodeNum[i] = -1, fileLock[i] = 0;
}
// ��ȡ�յ��ڴ�i���
int INodeListInRam::getFreeNode()
{
    for(int i = 0; i < INODET_IN_RAM; i++)
    {
        if(!iNodeList[i].check())
        {
            return i;
        }
    }
    return -1;
}
// ����һ��i���
bool INodeListInRam::loadNode(INode A, int id)
{
    int i = getFreeNode();
    if(i == -1){
        return false;
    }
        //return false;
    iNodeList[i] = A;
    iNodeNum[i] = id;
    return true;
}
// �ͷ�һ��i���
INode INodeListInRam::freeNode(int id)
{
    INode t;
    int i = searchNode(id);
    if(i == -1)
        return t;
    t = iNodeList[i];
    iNodeList[i].clear();
    iNodeNum[i] = -1;
    fileLock[i] = 0;
    return t;
}
INode& INodeListInRam::getNode(int id)
{
    int i = searchNode(id);
//    INode t;
//    if(i == -1)
//        return t;
    return iNodeList[i];
}
// Ѱ��id����Ӧ���ڴ�i�����±�
int INodeListInRam::searchNode(int id)
{
    for(int i = 0; i < INODET_IN_RAM; i++)
        if(iNodeNum[i] == id)
            return i;
    return -1;
}
// �û�username���±�Ϊid��inode��Ӧ���ļ�����
bool INodeListInRam::setLock(string username, int lock, int id)
{
    if(lock < 0 || lock > 2)
        return false;
    int i = searchNode(id);
    if(iNodeList[i].getUser() == username)
        fileLock[i] = lock;
    else
        return false;
    return true;
}



// �չ��캯��
FileOpenItem::FileOpenItem(){}

// ���ƹ��캯��
FileOpenItem::FileOpenItem(FileOpenItem &ano)
: offSet(ano.offSet)
, linkN(ano.linkN)
, flags(ano.flags)
, mode(ano.mode)
, id(ano.id){}

// ��ֵ���캯��
FileOpenItem::FileOpenItem(int offset, int flags, int mode, int id)
: offSet(offset)
, linkN(1)
, flags(flags)
, mode(mode)
, id(id){}

// ��ȡinode��id
int FileOpenItem::getId()
{
    return id;
}

// ��ȡƫ����
int FileOpenItem::getOffset()
{
    return offSet;
}

// ����ƫ����
bool FileOpenItem::setOffset(int offset)
{
    this->offSet = offset;
    return true;
}

// ����ļ�����
void FileOpenItem::clear()
{
    offSet = flags = mode = linkN = 0;
    id = -1;
}

// ��ȡ������
int FileOpenItem::getLink()
{
    return linkN;
}

// ��������
void FileOpenItem::icrLink()
{
    linkN++;
}

// ��������
void FileOpenItem::dcrLink()
{
    linkN--;
}

//��ʾ��Ϣ
void FileOpenItem::show()
{
    cout << "offset = " << offSet << ",linkN = " << linkN << ",flag = " << flags << ",mode = " << mode << ",id = " << id;
}

// ��ȡģʽ
int FileOpenItem::getMode()
{
    return mode;
}



int FileOpenList::size()
{
    return fileOpenSize;
}
// ���
void FileOpenList::clear()
{
    for(int i = 0; i < MAX_FDS; i++)
    {
        if(fileOpenList[i].getLink() > 0)
            fileOpenList[i].clear();
    }
    fileOpenSize = 0;
}

// ɾ������
bool FileOpenList::deleteLink(int id)
{
    if(fileOpenList[id].getLink() <= 0)
        return false;
    fileOpenList[id].dcrLink();
    if(fileOpenList[id].getLink() == 0)
    {
        deleteItem(id);
        return true;
    }
    return false;
}

// ��������
bool FileOpenList::addLink(int id)
{
    if(fileOpenList[id].getLink() < 0)
        return false;
    fileOpenList[id].icrLink();
    return true;
}

// ɾ��ĳһ��
bool FileOpenList::deleteItem(int id)
{
    if(fileOpenList[id].getLink() < 0)
        return false;
    fileOpenList[id].clear();
    fileOpenSize--;
    return true;
}

// ���ĳһ��
int FileOpenList::addItem(int offset, int flags, int mode, int id)
{
    int i = getFreeItem();
    if(i == -1)
        return -1;
    FileOpenItem t(offset, flags, mode, id);
    fileOpenList[i] = t;
    fileOpenSize++;
    return i; // ����ϵͳ�ļ��򿪱���±�
}

// ��ȡ���п�
int FileOpenList::getFreeItem()
{
    for(int i = 0; i < MAX_FDS; i++)
        if(fileOpenList[i].getLink() == 0)
            return i;
    return -1;
}

// ��ȡĳһ���inode���
int FileOpenList::getItemINode(int id)
{
    if(fileOpenList[id].getLink() == 0)
        return -1;
    else
        return fileOpenList[id].getId();
}

//��ʾ��Ϣ
void FileOpenList::show()
{
    cout << "\n��������������������������������������������\n";
    for(int i = 0; i < fileOpenCapacity; i++)
        if(fileOpenList[i].getLink() != 0)
        {
            fileOpenList[i].show();
            cout << endl;
        }
    cout << "\n��������������������������������������������\n";
}
// ��ȡƫ����
int FileOpenList::getOffset(int id)
{
    return fileOpenList[id].getOffset();
}
// ����ƫ����
void FileOpenList::setOffset(int id, int offset)
{
    fileOpenList[id].setOffset(offset);
}
// ��ȡģʽ
int FileOpenList::getMode(int id)
{
    return fileOpenList[id].getMode();
}



UserOpenItem::UserOpenItem(){}

UserOpenItem::UserOpenItem(int descriptor, int id)
: descriptor(descriptor)
, id(id){}
// ���
void UserOpenItem::clear()
{
    descriptor = id = -1;
}
// ����ֵ
void UserOpenItem::set(int descriptor, int id)
{
    this->descriptor = descriptor;
    this->id = id;
}
// ��ȡ������
int UserOpenItem::getDescriptor()
{
    return descriptor;
}
// ��ȡid
int UserOpenItem::getId()
{
    return id;
}
// ����Ƿ����
bool UserOpenItem::check()
{
    if(descriptor < 0)
        return false;
    return true;
}


UserOpenList::UserOpenList(){}
// ��ֵ���캯��
UserOpenList::UserOpenList(string username)
        : username(username){}
// ���
void UserOpenList::clear()
{
    username = "";
    for(int i = 0; i < MAX_USER_FD; i++)
        iNodeToFile[i].clear();
}
// ��ȡϵͳ�ļ��򿪱��±�
int UserOpenList::getFileId(int iNodeId, int num)
{
    int id = searchId(iNodeId, num);
    if(id == -1)
        return -1;
    return iNodeToFile[id].getId();
}
//Ѱ���±�
int UserOpenList::searchId(int iNodeId, int num)
{
    for(int i = 0; i < MAX_USER_FD; i++)
        if(iNodeToFile[i].getDescriptor() == iNodeId)
        {
            num--;
            if(num == 0)
                return i;
        }
    return -1;
}
// Ѱ�ҿ����±�
int UserOpenList::searchFreeItem()
{
    for(int i = 0; i < MAX_USER_FD; i++)
        if(iNodeToFile[i].check() == false)
            return i;
    return -1;
}
// ���һ����
bool UserOpenList::addItem(int iNodeId, int fileId)
{
    int id = searchFreeItem();
    if(id == -1)
        return false;
    UserOpenItem t(iNodeId, fileId);
    iNodeToFile[id] = t;
    return true;
}
// ɾ��һ����
bool UserOpenList::deleteItem(int iNodeId)
{
    int id = searchId(iNodeId);
    if(id == -1)
        return false;
    iNodeToFile[id].clear();
    return true;
}
// ��ȡ�û���
string UserOpenList::getUserName()
{
    return username;
}
//����
int UserOpenList::count(int iNodeId)
{
    int count = 0;
    for(int i = 0; i < MAX_USER_FD; i++)
        if(iNodeToFile[i].getDescriptor() == iNodeId)
            count++;
    return count;
}

