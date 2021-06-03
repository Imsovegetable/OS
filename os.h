//
// Created by 旧城筱雨 on 2021/6/2.
//
#include <iostream>
#include <conio.h>
#include <bits/stdc++.h>
#include "memory.h"
#include "gcm.h"
#include "directory.h"
#include "help.h"
#include "ram.h"
#include "fileSys.h"
#include "user.h"
#include "inode.h"

using namespace std;

#ifndef OS_OS_H
#define OS_OS_H

class OS{
public:
    void printTitle();
    void run();
    void help();
};

extern OS os;

#endif //OS_OS_H
