#include <bits/stdc++.h>

#include "memory.h"

using namespace std;

int main() {
    MixIndex index;
    for(int i = 1; i <= 16; i++)
        index.addIndex(i);
    index.show();
    for(int i= 1; i <= 9; i++)
        index.dropIndex();
    index.show();
    return 0;
}
