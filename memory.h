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
    int sign;
    int indexSize = 0;
    vector<int> indexes;
    vector<NormalIndex> indexTables;

public:
    NormalIndex(int sign = 0);

    NormalIndex(const NormalIndex&);

    NormalIndex& operator=(const NormalIndex&);
    //作为末级索引的功能
    // 获取第n个索引
    int getIndex(int n);
    // 添加磁盘块号为id的新索引
    bool addIndex(int id);
    // 获取索引块中索引的数量
    int size() const;
    // 从索引块中删除n个索引
    bool dropIndex(int n);
    // 删除最后一个索引
    bool dropIndex();

    //作为中间索引的功能
    // 从索引块中获取第n个下一级索引表
    NormalIndex& getNxtIndex(int n);
    // 添加一个下一级索引表
    bool addNxtIndex();
    // 删除后n个下一级索引表
    bool dropNxtIndex(int n);
    // 删除最后一个下一级索引表
    bool dropNxtIndex();
    // 查询sign值
    int check() const;
    // 显示辅助信息
    void show();
    // 清空
    void clear();

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

    // 添加直接索引
    bool addDirectIndex(int id);
    // 添加一次间接索引
    bool addOneIndirectIndex(int id);
    // 添加二次间接索引
    bool addTwoIndirectIndex(int id);
    // 添加三次间接索引
    bool addThreeIndirectIndex(int id);
    // 删除直接索引
    bool dropDirectIndex();
    // 删除一次间接索引
    bool dropOneInDirectIndex();
    // 删除二次间接索引
    bool dropTwoInDirectIndex();
    // 删除三次间接索引
    bool dropThreeInDirectIndex();

public:
    MixIndex();

    MixIndex(MixIndex&);

    MixIndex& operator=(const MixIndex&);
    // 添加一个索引
    bool addIndex(int id);
    // 返回索引数量
    int size() const;
    // 展示信息
    void show();
    // 删除一个索引
    bool dropIndex();
    // 清空信息
    void clear();
};



#endif //OS_MEMORY_H
