//
// Created by �ɳ����� on 2021/5/27.
//
#include "directory.h"

Directory* current_dir;

Directory::Directory(){}

Directory::Directory(Directory& ano)
: directory(ano.directory)
{}

Directory& Directory::operator=(const Directory & ano)
{
    directory = ano.directory;
    return *this;
}
// ���һ��Ŀ¼��
bool Directory::addItem(string filename, int id)
{
    if(directory[filename] != 0)
        return false;
    else
        directory[filename] = id;
    return true;
}

// ɾ��һ��Ŀ¼��
bool Directory::deleteItem(string filename)
{
    if(directory[filename] == 0)
        return false;
    else
        directory.erase(filename);
    return true;
}

//���Ŀ¼
void Directory::clear()
{
    directory.clear();
}
// ���ĳһ��Ŀ¼���Ƿ����
bool Directory::checkItem(string filename)
{
    return directory[filename] != 0;
}

// ��ȡĳ��Ŀ¼���i����
int Directory::getItem(string filename)
{
    if(directory[filename] == 0)
        return 0;
    else
        return directory[filename];
}

// Ŀ¼��������
bool Directory::setFileName(string filename, string newName)
{
    if(directory[filename] == 0 || directory[newName] != 0)
        return false;
    else
    {
        directory[newName] = directory[filename];
        directory.erase(filename);
        return true;
    }
}

// ���ش�С
int Directory::size()
{
    return directory.size();
}

// Ŀ¼��ʼ��
void Directory::init(int idSelf, int idParent)
{
    directory["."] = idSelf;
    directory[".."] = idParent;
}