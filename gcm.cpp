//
// Created by 旧城筱雨 on 2021/5/26.
//

#include "gcm.h"

// 构造函数
GroupLeader::GroupLeader():nextLeader(nullptr){}

GroupLeader::GroupLeader(GroupLeader* ano):nextLeader(ano){}

// 复制构造函数
GroupLeader::GroupLeader(GroupLeader& ano)
{
    this->groupSize = ano.groupSize;
    this->nextLeader = ano.nextLeader;
    this->groups = ano.groups;
}

// 获取当前组大小
int GroupLeader::size() const
{
    return groupSize;
}

// 获取一个空闲块的块号
int GroupLeader::get()
{
    int t = groups.top();
    groups.pop();
    groupSize--;
    return t;
}

// 往组里添加一个空闲块
bool GroupLeader::add(int id)
{
    if(groupSize >= groupCapacity) // 当前组已满
        return false;
    else
    {
        groups.push(id);
        groupSize++;
        return true;
    }
}

//返回自身的地址
GroupLeader* GroupLeader::self()
{
    return this;
}

//返回下一个组长块地址
GroupLeader* GroupLeader::nextSelf()
{
    return nextLeader;
}

// 设置下一个组长块
bool GroupLeader::setNextLeader(GroupLeader* ano)
{
    nextLeader = ano;
    return true;
}

// 获得一个空闲块
int SuperGroup::getFreeBlock()
{
    if(groupTotalSize <= 0)
        return -1;
    if(curGroup->size() <= 0)
        curGroup = curGroup->nextSelf();
    int t = curGroup->get();
    groupTotalSize--;
    return t;
}

// 返回一个被释放的块
bool SuperGroup::addNewBlock(int id)
{
    if(curGroup->size() >= 50)
    {
        GroupLeader* t = curGroup->self();
        curGroup = new GroupLeader(t);
    }
    curGroup->add(id);
    groupTotalSize++;
    return true;
}

// 获取总空闲块数
int SuperGroup::size() const
{
    return groupTotalSize;
}

// 初始化超级栈
void SuperGroup::init()
{
    for(int i = 0; i < TOTAL_GROUP_SIZE / GROUP_SIZE; i++)
    {
        GroupLeader* t; // 声明工作变量
        if(i == 0) // 将最先声明的组长块赋给当前超级块
        {
            t = new GroupLeader;
            curGroup = t;
        }
        else
        {
            auto *t1 = new GroupLeader; // 声明新的组长块
            t->setNextLeader(t1); // 链接到上一轮的组长块
            t = t1; // 交换变量
        }
        for(int j = GROUP_SIZE; j >= 1 ; j--) // 给每一组链接空闲块
        {
            t->add(i * GROUP_SIZE + j);
        }
    }
}

// 显示信息
void SuperGroup::show()
{
    cout << "\n——————————————————————————\n";
    cout << "当前超级栈容量为" << curGroup->size() << endl;
    cout << "获取一个空闲块块号为" << getFreeBlock() << endl;
    cout << "\n——————————————————————————\n";
}
