//
// Created by �ɳ����� on 2021/5/27.
//
#include "directory.h"
using namespace std;


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
    if(directory.find(filename) != directory.end())
        return false;
    else
        directory[filename] = id;
    return true;
}

// ɾ��һ��Ŀ¼��
bool Directory::deleteItem(string filename)
{
    if(directory.find(filename) == directory.end())
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
    return directory.find(filename) != directory.end();
}

// ��ȡĳ��Ŀ¼���i����
int Directory::getItem(string filename)
{
    if(directory.find(filename) == directory.end())
        return -1;
    else
        return directory[filename];
}

// Ŀ¼��������
bool Directory::setFileName(string filename, string newName)
{
    if(directory.find(filename) == directory.end() || directory.find(newName) != directory.end())
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

//����Ŀ¼���ļ��ĸ���
int Directory::getFileNumFromDir() {
    map<string, int>::iterator iter;
    int cnt = 0;
    for(iter=directory.begin(); iter!=directory.end(); iter++){
        cnt++;
    }
    return cnt;
}

//��Ŀ¼map������ת��Ϊstring���ͱ��ڴ洢
string Directory::save_as_string_dir() {
    map<string, int>::iterator iter;
    string ans;
    for(iter=directory.begin(); iter!=directory.end(); iter++){
        ans += (iter->first +'\n');
        ans += (to_string(iter->second) + '\n');
    }
    return ans;
}

string Directory::getFileName(int id)
{
    for(auto& it:directory)
    {
        if(it.second == id)
            return it.first;
    }
    return "";
}
