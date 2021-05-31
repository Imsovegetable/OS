//
// Created by 旧城筱雨 on 2021/5/27.
//

#include "help.h"
#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

int statistic(const string& filename)
{
    ifstream fin(filename);
    if(!fin.is_open())
        return -1;
    string t;
    fin >> noskipws >> t;
    return t.size();
}

extern string getcurrentTime()
{
    time_t now = time(0);
    char *dt = ctime(&now);
    string current_time = string(dt);
    return current_time;
}

//获取本地电脑主机名，用来进行菜单显示
extern string getLocalIpName() {
    TCHAR buf[MAX_COMPUTERNAME_LENGTH + 2];
    DWORD buf_size;
    buf_size = sizeof buf - 1;
    GetComputerName(buf, &buf_size);
    string a = buf;
    return a;
}
