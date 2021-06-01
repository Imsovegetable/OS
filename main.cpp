
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

void printTitle()
{
    string path = "";
    if(current_user == "")
    {
        cout << "$\\>";
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
        path = "\\" + name + "\\" + path;
        cout << "$" << path << ">";
        return;
    }
}

int main()
{
    fileSys.init();
    fileSys.users.createUser("cyndsb", "cyndsb");
//    printTitle();
    fileSys.users.login("cyndsb", "cyndsb");
//    cout << endl;

//    cout << current_user << endl;
    int i = fileSys.createUserDirectory("cyndsb");
//    cout << fileSys.superBlock.iNodeList.getInode(i).getUser() << endl;
    fileSys.users.setCurDir(&(fileSys.superBlock.iNodeList.getInode(i).dir));
//    printTitle();
    fileSys.directoryCreate("111");
    fileSys.fileCreate("cynddsb");
    cout << fileSys.superBlock.iNodeList.iNodeSize << endl;

	return 0;
}





