//
// Created by 旧城筱雨 on 2021/5/27.
//

#include "help.h"

int statictic(string filename)
{
    ifstream fin(filename);
    if(!fin.is_open())
        return -1;
    string t = "";
    fin >> noskipws >> t;
    return t.size();
}

string getcurrentTime()
{
    time_t now = time(0);
    char *dt = ctime(&now);
    string current_time = string(dt);
    return current_time;
}