//
// Created by 旧城筱雨 on 2021/5/25.
//
#include <bits/stdc++.h>
#include "GODNING.h"

#ifndef OS_MEMORY_H
#define OS_MEMORY_H

using namespace std;

// 普通索引表
class NormalIndex{
private:
    const int indexCapacity = IDXT_SIZE;
    const int sign;
    int indexSize = 0;
    vector<int> indexes;
    vector<NormalIndex> indexTables;

public:
    NormalIndex(int sign):sign(sign){}

    //作为末级索引的功能

    // 获取第n个索引
    int getIndex(int n)
    {
        if(n >= indexSize || n < 0) // n超出范围
            return -1;
        else
            return indexes[n];
    }
    // 添加磁盘块号为id的新索引
    bool addIndex(int id)
    {
        if(id < 0 || indexSize >= indexCapacity) // id超出范围或索引块已满
            return false;
        else
        {
            indexes.push_back(id);
            indexSize++;
            return true;
        }
    }
    // 获取索引块中索引的数量
    int size()
    {
        return indexSize;
    }
    // 从索引块中删除n个索引
    bool dropIndex(int n)
    {
        if(n > indexSize || n <= 0) // n超出范围
            return false;
        else
        {
            for(int i = indexSize - 1; i > indexSize - 1 - n; i--) // 删除后n个索引的内容
                indexes.pop_back();
            indexSize -= n;
            return true;
        }
    }
    // 删除最后一个索引
    bool dropIndex()
    {
        if(indexSize > 0)
        {
            indexes.pop_back();
            indexSize--;
            return true;
        }
        return false;
    }

    //作为中间索引的功能

    // 从索引块中获取第n个下一级索引表
    NormalIndex& getNxtIndex(int n)
    {
        return indexTables[n];
    }
    // 添加一个下一级索引表
    bool addNxtIndex()
    {
        if(indexSize >= indexCapacity)
            return false;
        else {
            NormalIndex *t = new NormalIndex(sign - 1);
            indexTables.push_back(*t);
            indexSize++;
            return true;
        }
    }
    // 删除后n个下一级索引表
    bool dropNxtIndex(int n)
    {
        if(n > indexSize || n <= 0) // n超出范围
            return false;
        else
        {
            for(int i = indexSize - 1; i > indexSize - 1 - n; i--) // 删除后n个索引的内容
                indexTables.pop_back();
            indexSize -= n;
            return true;
        }
    }
    // 删除最后一个下一级索引表
    bool dropNxtIndex()
    {
        if(indexSize > 0)
        {
            indexTables.pop_back();
            indexSize--;
            return true;
        }
        return false;
    }
    // 查询sign值
    int check()
    {
        return sign;
    }
    // 显示辅助信息
    void show()
    {
        cout << "\n";
        for(int i = 0; i < indexSize; i++)
            cout << indexes[i] << " ";
        cout << "\n";
    }
};


// 混合索引表
class MixIndex{
private:
    const int indexCapacity = MIX_IDXT_SIZE;
    int indexSize = 0;
    vector<int> indexes;
    NormalIndex oneIndirectIndex;
    NormalIndex twoIndirectIndex;
    NormalIndex threeIndirectIndex;

public:
    MixIndex(): oneIndirectIndex(0), twoIndirectIndex(1), threeIndirectIndex(2){}

    // 添加一个索引
    bool addIndex(int id)
    {
        if(indexSize >= indexCapacity || id < 0) // 索引已经满了或者id超出范围
            return false;
        else
        {
            if(indexSize < BASIC_IDX) // 直接索引
                return addDirectIndex(id);
            else if(indexSize >= BASIC_IDX && indexSize < BASIC_IDX + IDXT_SIZE) // 一次间接索引
                return addOneIndirectIndex(id);
            else if(indexSize >= BASIC_IDX + IDXT_SIZE && indexSize < BASIC_IDX + IDXT_SIZE + ONE_IDXT_SIZE) // 两次间接索引
                return addTwoIndirectIndex(id);
            else if(indexSize >= BASIC_IDX + IDXT_SIZE + ONE_IDXT_SIZE && indexSize < MIX_IDXT_SIZE) // 三次简介索引
                return addThreeIndirectIndex(id);
            else
                return false;
        }
    }
    // 添加直接索引
    bool addDirectIndex(int id)
    {
        indexes.push_back(id);
        indexSize++;
        return true;
    }
    // 添加一次间接索引
    bool addOneIndirectIndex(int id)
    {
        oneIndirectIndex.addIndex(id);
        indexSize++;
        return true;
    }
    // 添加二次间接索引
    bool addTwoIndirectIndex(int id)
    {
        // 计算超出前两部分索引的数量
        int n = indexSize - BASIC_IDX - IDXT_SIZE;
        if(n % IDXT_SIZE == 0) //正好填满前一个二次间址索引块
            twoIndirectIndex.addNxtIndex(); // 新建一个索引块

        //获得当前未满的二次间址索引块
        NormalIndex &t = twoIndirectIndex.getNxtIndex(n / IDXT_SIZE);
        t.addIndex(id);
        indexSize++;
        return true; // 添加索引
    }
    // 添加三次间接索引
    bool addThreeIndirectIndex(int id)
    {
        // 计算超出前三部分索引的数量
        int n = indexSize - BASIC_IDX - IDXT_SIZE - ONE_IDXT_SIZE;
        if(n % ONE_IDXT_SIZE == 0) // 正好填满前一个二次间址索引块
            threeIndirectIndex.addNxtIndex(); // 新建一个二次间址索引块

        // 获得当前未满的二次间址索引块
        NormalIndex &t = threeIndirectIndex.getNxtIndex(n / ONE_IDXT_SIZE);
        if(n % IDXT_SIZE == 0) // 正好填满一个三次间址索引块
            t.addNxtIndex(); // 新建一个三次间址索引块

        // 获得当前未满的三次间址索引块
        NormalIndex &nxt = t.getNxtIndex((n % ONE_IDXT_SIZE) / IDXT_SIZE);
        nxt.addIndex(id);
        indexSize++;
        return true; // 添加索引
    }
    // 返回索引数量
    int size()
    {
        return indexSize;
    }
    // 展示信息
    void show()
    {
        cout << "——————————————————————————————\n";
        cout << "直接索引区：\n";
        for(int i = 0; i < min(indexSize, BASIC_IDX); i++)
            cout << indexes[i] << " ";
        cout << "\n";
        cout << "一次间接索引区：";
        if(indexSize >= BASIC_IDX)
        {
            oneIndirectIndex.show();
        }
        cout << "二次间接索引区：";
        if(indexSize >= BASIC_IDX + IDXT_SIZE)
        {
            int n = twoIndirectIndex.size();
            for(int i = 0; i < n; i++)
                twoIndirectIndex.getNxtIndex(i).show();
        }
        cout << "三次间接索引区：";
        if(indexSize >= BASIC_IDX + IDXT_SIZE + ONE_IDXT_SIZE)
        {
            int n = threeIndirectIndex.size();
            for(int i = 0; i < n; i++)
            {
                int m = threeIndirectIndex.getNxtIndex(i).size();
                for(int j = 0; j < m; j++)
                    threeIndirectIndex.getNxtIndex(i).getNxtIndex(j).show();
            }
        }
        cout << "\n——————————————————————————————\n";
    }
    // 删除一个索引
    bool dropIndex()
    {
        if(indexSize <= 0)
            return false;
        else if(indexSize <= BASIC_IDX) // 直接索引
            return dropDirectIndex();
        else if(indexSize <= BASIC_IDX + IDXT_SIZE) // 一次间接索引
            return dropOneInDirectIndex();
        else if(indexSize <= BASIC_IDX + IDXT_SIZE + ONE_IDXT_SIZE) // 二次间接索引
            return dropTwoInDirectIndex();
        else
            return dropThreeInDirectIndex(); // 三次间接索引
    }
    // 删除直接索引
    bool dropDirectIndex()
    {
        indexes.pop_back();
        indexSize--;
        return true;
    }
    // 删除一次间接索引
    bool dropOneInDirectIndex()
    {
        oneIndirectIndex.dropIndex();
        indexSize--;
        return true;
    }
    // 删除二次间接索引
    bool dropTwoInDirectIndex()
    {
        // 计算超出前两部分的索引数量
        int n = indexSize - BASIC_IDX - IDXT_SIZE - 1; //这里的减一非常重要！因为size是从1开始的，下标则是从0开始，导致除法时跳到下一个块
        // 找到对应的二次间址索引块
        twoIndirectIndex.getNxtIndex(n / IDXT_SIZE).dropIndex();
        indexSize--;
        // 此处n的含义应是数量而不是下标，因此要把减一补偿回来
        if((n + 1) % IDXT_SIZE == 1) // 如果删除的正好是二次间址索引块的最后一个索引
            twoIndirectIndex.dropNxtIndex(); // 把索引块也删除
        return true;
    }
    // 删除三次间接索引
    bool dropThreeInDirectIndex()
    {
        // 计算超出前三部分的索引数量
        int n = indexSize - BASIC_IDX - IDXT_SIZE - ONE_IDXT_SIZE - 1;// 同上，一定要减一
        // 找到对应的三次间址索引块
        threeIndirectIndex.getNxtIndex(n / ONE_IDXT_SIZE).getNxtIndex((n % ONE_IDXT_SIZE) / IDXT_SIZE).dropIndex();
        indexSize--;
        // 此处n的含义应是数量而不是下标，因此要把减一补偿回来
        if(((n + 1) % ONE_IDXT_SIZE) % IDXT_SIZE == 1) // 如果删除的正好是三次间址索引块的最后一个索引
            threeIndirectIndex.getNxtIndex(n / ONE_IDXT_SIZE).dropNxtIndex(); // 把这个三次间址索引块也删除
        // 此处n的含义应是数量而不是下标，因此要把减一补偿回来
        if((n + 1) % ONE_IDXT_SIZE == 1) // 如果删除的正好是二次间址索引块的最后一个索引
            threeIndirectIndex.dropNxtIndex(); // 把这个二次间址索引块也删除
        return true;
    }
};



#endif //OS_MEMORY_H
