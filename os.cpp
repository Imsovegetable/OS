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
        if(cmd == "login") // 登录
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
        else if(cmd == "cd") // 进入目录
        {
            string index;
            cin >> index;
            fileSys.cd(index);
        }
        else if(cmd == "mkdir") //创建目录
        {
            string index;
            cin >> index;
            fileSys.directoryCreate(index);
        }
        else if(cmd == "dir") // 展示列表
        {
            fileSys.showDir();
        }
        else if(cmd == "create") // 创建文件
        {
            string filename;
            cin >> filename;
            fileSys.fileCreate(filename);
        }
        else if(cmd == "open") // 打开文件
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
        else if(cmd == "close") // 关闭文件
        {
            string filename;
            cin >> filename;
            fileSys.closeFile(filename);
        }
        else if(cmd == "read") // 读取文件
        {
            string filename;
            cin >> filename;
            int len;
            cin >> len;
            cout << fileSys.readFile(filename, len);
        }
        else if(cmd == "write") // 写入文件
        {
            string filename;
            cin >> filename;
            string content;
            getline(cin, content);
            content = content.substr(1);
            fileSys.writeFile(filename, content);
//            cout << endl;
        }
        else if(cmd == "delete") // 删除文件
        {
            string filename;
            cin >> filename;
            fileSys.fileDelete(filename);
        }
        else if(cmd == "logout") // 登出
        {
            fileSys.users.loginOut();
        }
        else if(cmd == "rmdir") // 删除目录
        {
            string filename;
            cin >> filename;
            fileSys.directoryDelete(filename);
        }
        else if(cmd == "format") // 格式化
        {
            cout << "please input the admin password:";
            string s;
            cin >> s;
            if(s == ADMINPASSWORD)
                fileSys.formatFileSystem();
            else
                cout << "you are not authenticated!\n";
        }
        else if(cmd == "cl") // 改变登录账号
        {
            string username;
            cin >> username;
            fileSys.users.switchUser(username);
//            cout << current_user << endl;
        }
        else if(cmd == "justcopy") // 复制
        {
            string filename;
            cin >> filename;
            fileSys.copy(filename);
        }
        else if(cmd == "paste") // 粘贴
        {
            fileSys.paste();
        }
        else if(cmd == "cut") // 剪切
        {
            string filename;
            cin >> filename;
            fileSys.cut(filename);
        }
        else if(cmd == "rename") // 文件重命名
        {
            string filename, newName;
            cin >> filename >> newName;
            fileSys.fileRename(filename, newName);
        }
        else if(cmd == "fseek") // 文件内重定位
        {
            string filename;
            int offset;
            cin >> filename >> offset;
            fileSys.fSeek(filename, offset);
        }
        else if(cmd == "showindex") // 显示文件信息
        {
            string filename;
            cin >> filename;
            fileSys.showFile(filename);
        }
        else if(cmd == "exit") // 退出
        {
            exit(0);
        }
        else if(cmd == "help") // 帮助
        {
            help();
        }
        else if(cmd == "save") // 保存
        {
            fileSys.saveInodeInfo();
        }
        else if(cmd == "readInfo") // 读取
        {
            fileSys.readInodeInfo();
        }
        else if(cmd == "copy") // 复制到当前目录另一文件
        {
            string filename, newName;
            cin >> filename >> newName;
            fileSys.copy2(filename, newName);
        }
        else if(cmd == "show")
        {
            string filename;
            cin >> filename;
            fileSys.show(filename);
        }
        else if(cmd == "add")
        {
            string filename, newName;
            cin >> filename >> newName;
            fileSys.add(filename, newName);
        }
    }
}

void OS::help()
{
    cout << "login\t\t\t\t   登录\n";                     cout << "logout\t\t\t\t\t登出\n";
    cout << "cd\tdirname\t\t\t\t进入目录\n";              cout << "mkdir\tdirname\t\t\t\t创建目录\n";
    cout << "rmdir\tdirname\t\t\t\t删除目录\n";           cout << "create\tfilename\t\t\t创建文件\n";
    cout << "open\tfilename\t\t\t打开文件\n";           cout << "close\tfilename\t\t\t关闭文件\n";
    cout << "read\tfilename\tlength\t\t读取文件\n";   cout << "write\tfilename\tcontent\t\t写入文件\n";
    cout << "delete\tfilename\t\t\t删除文件\n";         cout << "format\t\t\t\t\t格式化\n";
    cout << "cl\tusername\t\t\t切换用户\n";             cout << "justcopy\tfilename\t\t\t复制\n";
    cout << "paste\t\t\t\t\t粘贴\n";                     cout << "cut\tfilename\t\t\t剪切\n";
    cout << "rename\tfilename\tnewname\t\t重命名\n";  cout << "fseek\toffset\t\t\t\t重定位\n";
    cout << "show\tfilename\t\t\t显示文件内容\n";        cout << "showindex\tfilename\t\t\t显示文件使用块信息\n";
    cout << "exit\t\t\t\t\t退出\n";
    cout << "add\tfilename\tnewname\t\t追加文件内容\n";  cout << "copy\tfilename\tnewname\t\t复制文件内容\n";
}