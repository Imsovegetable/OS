//
// Created by �ɳ����� on 2021/5/27.
//
#include <bits/stdc++.h>

#ifndef OS_DIRECTORY_H
#define OS_DIRECTORY_H


using namespace std;

class Directory{
private:
    //Ŀ¼��
    map<string, int> directory;

public:
    //
    Directory();

    Directory(Directory&);

    Directory& operator=(const Directory&);
    // ���һ��Ŀ¼��
    bool addItem(string filename, int id);
    // ɾ��һ��Ŀ¼��
    bool deleteItem(string filename);
    // ���ĳһ��Ŀ¼���Ƿ����
    bool checkItem(string filename);
    // ��ȡĳ��Ŀ¼���i����
    int getItem(string filename);
    // Ŀ¼��������
    bool setFileName(string filename, string newName);
    // ���ش�С
    int size();
    // Ŀ¼��ʼ��
    void init(int idSelf, int idParent);
    // ���Ŀ¼
    void clear();
    // ��ʾ��Ϣ
    void show()
    {
        cout << "\n������������������������������������������������������������\n";
        for(auto& it: directory)
            cout << it.first << " " << it.second << endl;
        cout << "������������������������������������������������������������\n";
    }
    //��ȡĿ¼���������ļ�����
    int getFileNumFromDir();
    //��vectorת����string���ͱ��ڴ洢
    string save_as_string_dir();
};


#endif //OS_DIRECTORY_H
