
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
        cout << "$/>";
        return;
    }
    else
    {
        Directory* cur_dir;
        int id;
        string name;
        int pid;
        cur_dir = fileSys.users.getCurDir();
        Directory* t = cur_dir;
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
        cout << "$" << path << ">";
        fileSys.users.setCurDir(t);
        return;
    }
}

int main()
{
    fileSys.init();
    fileSys.users.createUser("cynsb", "cynsb");
    fileSys.users.login("cynsb", "cynsb");
    int i = fileSys.createUserDirectory("cynsb");
    fileSys.users.setCurDir(&(fileSys.superBlock.iNodeList.getInode(i).dir));
    fileSys.directoryCreate("111");
    fileSys.fileCreate("cyndsb");
    fileSys.openFile("cyndsb", 0, 1);
//    fileSys.userOpenList["cynsb"].show();
    fileSys.writeFile("cyndsb", "test12345");
    fileSys.writeFile("cyndsb", "cyndsb");
//    cout << fileSys.iNodeListInRam.getNode(fileSys.users.getCurDir()->getItem("cyndsb")).content << endl;
 //   fileSys.fileOpenList.setOffset(fileSys.userOpenList["cynsb"].getFileId(fileSys.users.getCurDir()->getItem("cyndsb"), 1), 0);
    fileSys.fileOpenList.setOffset(fileSys.userOpenList["cynsb"].getFileId(fileSys.users.getCurDir()->getItem("cyndsb"), 2), 0);
    cout << fileSys.readFile("cyndsb", 5);

//    fileSys.userOpenList["cynsb"].show();

//    cout << fileSys.users.getCurDir()->getItem(".") << endl;
//    fileSys.fileCreate("cynddsb");
//    fileSys.fileDelete("cynddsb");
//    fileSys.directoryDelete("");
//    fileSys.writeFile("cynndsb", "cyhnzsgdsb");
//
//    cout << fileSys.superBlock.iNodeList.iNodeSize << endl;
//    for(int j=0; j<fileSys.superBlock.iNodeList.iNodeSize; j++){
//        fileSys.superBlock.iNodeList.getSpecificInodeInfo(j);
//    }

	return 0;
}





