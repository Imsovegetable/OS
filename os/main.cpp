#include <bits/stdc++.h>

#include "memory.h"
//#include "assistant.cpp"
#include "INode.h"
#include "user.cpp"
using namespace std;

int main() {
    //cout<<CaculateFileSize("cyntest.txt")<<endl;
    cout<<IsExistedAuthor("cyhdsb")<<endl;
    MixIndex index;
    for(int i = 1; i <= 16; i++)
        index.addIndex(i);
    index.show();
    for(int i= 1; i <= 9; i++)
        index.dropIndex();
    index.show();
    return 0;
}
