
#include <bits/stdc++.h>
#include "os.h"

using namespace std;


int main()
{
    ifstream file("sign.txt");
    string sign;
    file >> sign;
    file.close();
    if(sign == "1"){
        //���signΪ1˵���Ѿ��������ļ�ϵͳ
        cout << "do you want to format the file system? [Y/N]:";
        string choice;
        cin >> choice;
        if(choice == "Y" || choice == "y"){
            fileSys.formatFileSystem();
            while(true)
            {
                cout << ">";
                string cmd;
                cin >> cmd;
                if(cmd == "init")
                {
                    fileSys.init();
                    break;
                }
            }
            os.run();
        }
        else{
            fileSys.readInodeInfo();
            os.run();
        }
    }
    if(sign == "0"){
        //osΪ0˵����û�д����ļ�ϵͳ
        while(true)
        {
            cout << ">";
            string cmd;
            cin >> cmd;
            if(cmd == "init")
            {
                fileSys.init();
                break;
            }
        }
        os.run();
    }
	return 0;
}





