//
// Created by 旧城筱雨 on 2021/5/27.
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
// 添加一个目录项
bool Directory::addItem(string filename, int id)
{
    if(directory[filename] != 0)
        return false;
    else
        directory[filename] = id;
    return true;
}

// 删除一个目录项
bool Directory::deleteItem(string filename)
{
    if(directory[filename] == 0)
        return false;
    else
        directory.erase(filename);
    return true;
}

//清空目录
void Directory::clear()
{
    directory.clear();
}
// 检查某一个目录项是否存在
bool Directory::checkItem(string filename)
{
    return directory[filename] != 0;
}

// 获取某个目录项的i结点号
int Directory::getItem(string filename)
{
    if(directory[filename] == 0)
        return 0;
    else
        return directory[filename];
}

// 目录项重命名
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

// 返回大小
int Directory::size()
{
    return directory.size();
}

// 目录初始化
void Directory::init(int idSelf, int idParent)
{
    directory["."] = idSelf;
    directory[".."] = idParent;
}