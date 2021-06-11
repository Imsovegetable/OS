
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
        //如果sign为1说明已经创建了文件系统
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
        //os为0说明还没有创建文件系统
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





