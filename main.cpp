
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

fileSystem fileSystem;

int main()
{


	return 0;
}


void printTitle()
{
    string path = "";
    if(current_user == "")
    {
        cout << "[/]$:";
        return;
    }
    else
    {
        Directory* cur_dir;
        int id;
        string name;
        int pid;
        cur_dir = fileSys.users.getCurDir();
        id = cur_dir->getItem(".");
        pid = cur_dir->getItem("..");
        cur_dir = fileSys.returnToParent();
        while(pid != 0)
        {
            name = fileSys.superBlock.iNodeList.getInode(pid).dir.getFileName(id);
            path = name + "/" + path;
            id = cur_dir->getItem(".");
            pid = cur_dir->getItem("..");
            cur_dir = fileSys.returnToParent();
        }
        name = fileSys.superBlock.iNodeList.getInode(pid).dir.getFileName(id);
        path = "/" + name + "/" + path;
        cout << "[" << path << "]$:";
        return;
    }
}


