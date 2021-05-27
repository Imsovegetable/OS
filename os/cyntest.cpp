//
// Created by Chen Yining on 2021/5/27.
//


#include<bits/stdc++.h>
using namespace std;

int CaculateFileSize(const string& filename){
    ifstream file(filename);
    if(!file.is_open())
        return -1;
    string t;
    file >> noskipws >> t;
    return t.size();
}

int main(){
    cout<<CaculateFileSize("users.txt")<<endl;
    return 0;
}

