//
// Created by �ɳ����� on 2021/6/2.
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
        if(cmd == "login") // ��¼
        {
            string username, password = "";
            cout << "username:";
            cin >> username;
            cout << "password:";
            cin >> password;
            //�������� IDE�����޷��ﵽԤ��Ч��
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
        else if(cmd == "cd") // ����Ŀ¼
        {
            string index;
            cin >> index;
            fileSys.cd(index);
        }
        else if(cmd == "mkdir") //����Ŀ¼
        {
            string index;
            cin >> index;
            fileSys.directoryCreate(index);
        }
        else if(cmd == "dir") // չʾ�б�
        {
            fileSys.showDir();
        }
        else if(cmd == "create") // �����ļ�
        {
            string filename;
            cin >> filename;
            fileSys.fileCreate(filename);
        }
        else if(cmd == "open") // ���ļ�
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
        else if(cmd == "close") // �ر��ļ�
        {
            string filename;
            cin >> filename;
            fileSys.closeFile(filename);
        }
        else if(cmd == "read") // ��ȡ�ļ�
        {
            string filename;
            cin >> filename;
            int len;
            cin >> len;
            cout << fileSys.readFile(filename, len);
        }
        else if(cmd == "write") // д���ļ�
        {
            string filename;
            cin >> filename;
            string content;
            getline(cin, content);
            content = content.substr(1);
            fileSys.writeFile(filename, content);
//            cout << endl;
        }
        else if(cmd == "delete") // ɾ���ļ�
        {
            string filename;
            cin >> filename;
            fileSys.fileDelete(filename);
        }
        else if(cmd == "logout") // �ǳ�
        {
            fileSys.users.loginOut();
        }
        else if(cmd == "rmdir") // ɾ��Ŀ¼
        {
            string filename;
            cin >> filename;
            fileSys.directoryDelete(filename);
        }
        else if(cmd == "format") // ��ʽ��
        {
            cout << "please input the admin password:";
            string s;
            cin >> s;
            if(s == ADMINPASSWORD)
                fileSys.formatFileSystem();
            else
                cout << "you are not authenticated!\n";
        }
        else if(cmd == "cl") // �ı��¼�˺�
        {
            string username;
            cin >> username;
            fileSys.users.switchUser(username);
//            cout << current_user << endl;
        }
        else if(cmd == "justcopy") // ����
        {
            string filename;
            cin >> filename;
            fileSys.copy(filename);
        }
        else if(cmd == "paste") // ճ��
        {
            fileSys.paste();
        }
        else if(cmd == "cut") // ����
        {
            string filename;
            cin >> filename;
            fileSys.cut(filename);
        }
        else if(cmd == "rename") // �ļ�������
        {
            string filename, newName;
            cin >> filename >> newName;
            fileSys.fileRename(filename, newName);
        }
        else if(cmd == "fseek") // �ļ����ض�λ
        {
            string filename;
            int offset;
            cin >> filename >> offset;
            fileSys.fSeek(filename, offset);
        }
        else if(cmd == "showindex") // ��ʾ�ļ���Ϣ
        {
            string filename;
            cin >> filename;
            fileSys.showFile(filename);
        }
        else if(cmd == "exit") // �˳�
        {
            exit(0);
        }
        else if(cmd == "help") // ����
        {
            help();
        }
        else if(cmd == "save") // ����
        {
            fileSys.saveInodeInfo();
        }
        else if(cmd == "readInfo") // ��ȡ
        {
            fileSys.readInodeInfo();
        }
        else if(cmd == "copy") // ���Ƶ���ǰĿ¼��һ�ļ�
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
    cout << "login\t\t\t\t   ��¼\n";                     cout << "logout\t\t\t\t\t�ǳ�\n";
    cout << "cd\tdirname\t\t\t\t����Ŀ¼\n";              cout << "mkdir\tdirname\t\t\t\t����Ŀ¼\n";
    cout << "rmdir\tdirname\t\t\t\tɾ��Ŀ¼\n";           cout << "create\tfilename\t\t\t�����ļ�\n";
    cout << "open\tfilename\t\t\t���ļ�\n";           cout << "close\tfilename\t\t\t�ر��ļ�\n";
    cout << "read\tfilename\tlength\t\t��ȡ�ļ�\n";   cout << "write\tfilename\tcontent\t\tд���ļ�\n";
    cout << "delete\tfilename\t\t\tɾ���ļ�\n";         cout << "format\t\t\t\t\t��ʽ��\n";
    cout << "cl\tusername\t\t\t�л��û�\n";             cout << "justcopy\tfilename\t\t\t����\n";
    cout << "paste\t\t\t\t\tճ��\n";                     cout << "cut\tfilename\t\t\t����\n";
    cout << "rename\tfilename\tnewname\t\t������\n";  cout << "fseek\toffset\t\t\t\t�ض�λ\n";
    cout << "show\tfilename\t\t\t��ʾ�ļ�����\n";        cout << "showindex\tfilename\t\t\t��ʾ�ļ�ʹ�ÿ���Ϣ\n";
    cout << "exit\t\t\t\t\t�˳�\n";
    cout << "add\tfilename\tnewname\t\t׷���ļ�����\n";  cout << "copy\tfilename\tnewname\t\t�����ļ�����\n";
}