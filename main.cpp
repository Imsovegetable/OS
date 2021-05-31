
#include <bits/stdc++.h>
#include "memory.h"
#include "gcm.h"
#include "directory.h"
#include "help.h"
#include "fileSys.h"
#include "user.h"
#include "inode.h"

using namespace std;

int main()
{

    cout << getLocalIpName() << endl;
    fileSystem sys;
    sys.users.readUserList();
    ///sys.users.createUser("cyn", "dsb");
    sys.users.login("cyn", "dsb");
    current_user = "cyn";
    cout<<sys.users.userList[0].getUsername()<<endl;

    sys.directoryCreate("mnt");
    //sys.users.setCurDir();
    sys.users.saveUser();
    //sys.directoryCreate("mnt");

//    int a = sys.superBlock.iNodeList.getFreeInodeNum();
//    INode A(1, getcurrentTime(), getcurrentTime(), "cyhdsb");
//    sys.superBlock.iNodeList.inodeList[a] = A;
//    iNodeDistributeList[a] = true;
//    //INode B(1, getcurrentTime(), getcurrentTime(), "cyhdsb");
    sys.saveInodeInfo();
//    INode B(0, getcurrentTime(), getcurrentTime(), "ca");
//    sys.superBlock.iNodeList.inodeList[a] = B;
//    sys.readInodeInfo();
//    cout<<sys.superBlock.iNodeList.inodeList[0].getUser()<<endl;
//    MixIndex index;
//    for(int i = 1; i <= 16; i++)
//        index.addIndex(i);
//    index.show();
//    for(int i= 1; i <= 9; i++)
//        index.dropIndex();
//    index.show();
//    vector<int> t = index.getIndexes();
//    for(int i = 0; i < t.size(); i++)
//        cout << t[i] << " ";

//    GroupLeader* group = new GroupLeader;
//    cout << group->size() << endl;
//    group->add(1);
//    cout << group->size() << endl;
//    cout << group->get() << endl;

//    SuperGroup* sg = new SuperGroup;
//    sg->init();
//    sg->show();

//    Directory d;
//    d.show();
//    d.init(3, 4);
//    d.show();
//    d.addItem("cyndsb.txt", 1);
//    d.addItem("cynzdsdsb.txt", 2);
//    d.show();
//    d.deleteItem("cyndsb.txt");
//    cout << d.checkItem("cynzdsdsb.txt") << endl;
//    cout << d.getItem("cynzdsdsb.txt") << endl;
//    cout << d.size() << endl;
//    d.show();

//    string n = "1.txt";
//    cout << statictic(n);
	return 0;
}