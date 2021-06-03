//
// Created by 旧城筱雨 on 2021/6/2.
//
#include "os.h"

OS os;

void OS::printTitle()
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
        if(id != pid)
        {
            name = fileSys.superBlock.iNodeList.getInode(pid).dir.getFileName(id);
            path = "/" + name + "/" + path;
        }
        else
        {
            path = "/";
        }
        cout << "$" << path << ">";
        fileSys.users.setCurDir(t);
        return;
    }
}

void OS::run()
{
    string cmd;
    while (true)
    {
//        system("cls");
        printTitle();
        cin >> cmd;
        if(cmd == "login")
        {
            string username, password = "";
            cout << "username:";
            cin >> username;
            cout << "password:";
            cin >> password;
            //密码隐藏 IDE问题无法达到预期效果
//            char c ;
//            while((c = getch() )!= 13)
//            {
//                password += c;
//            }
            bool state = fileSys.users.login(username, password);
            if(state)
                cout << "welcome " << username << endl;
            else
                cout << "wrong username or password" << endl;
        }
        else if(cmd == "cd")
        {
            string index;
            cin >> index;
            fileSys.cd(index);
        }
        else if(cmd == "mkdir")
        {
            string index;
            cin >> index;
            fileSys.directoryCreate(index);
        }
        else if(cmd == "dir")
        {
//            cout << fileSys.users.getCurDir()->getItem(".") << endl;
//            cout << fileSys.users.getCurDir()->size() << endl;
//            fileSys.users.showDir();
        }
        else if(cmd == "create")
        {
            string filename;
            cin >> filename;
            fileSys.fileCreate(filename);
        }
        else if(cmd == "open")
        {
            string filename;
            int sign, mode;
            cin >> filename;
            cout << "offset[0/1]:";
            cin >> sign;
            if(sign != 0 && sign != 1)
                sign = 0;
            cout << "mode[0/1]:";
            cin >> mode;
            if(mode != 0 && mode != 1)
                mode = 0;
            fileSys.openFile(filename, sign, mode);
        }
        else if(cmd == "close")
        {
            string filename;
            cin >> filename;
            fileSys.closeFile(filename);
        }
        else if(cmd == "read")
        {
            string filename;
            cin >> filename;
            int len;
            cin >> len;
            cout << fileSys.readFile(filename, len);
            cout << endl;
        }
        else if(cmd == "write")
        {
            string filename;
            cin >> filename;
            string content;
            getline(cin, content);
            content = content.substr(1);
            fileSys.writeFile(filename, content);
//            cout << endl;
        }
        else if(cmd == "delete")
        {
            string filename;
            cin >> filename;
            fileSys.fileDelete(filename);
        }
        else if(cmd == "logout")
        {
            fileSys.users.loginOut();
        }
        else if(cmd == "rmdir")
        {
            string filename;
            cin >> filename;
            fileSys.directoryDelete(filename);
        }
        else if(cmd == "format")
        {
            fileSys.formatFileSystem();
        }
        else if(cmd == "cl")
        {
            string username;
            cin >> username;
            fileSys.users.switchUser(username);
//            cout << current_user << endl;
        }
        else if(cmd == "copy")
        {
            string filename;
            cin >> filename;
            fileSys.copy(filename);
        }
        else if(cmd == "paste")
        {
            fileSys.paste();
        }
    }
}