//
// Created by �ɳ����� on 2021/5/26.
//

#include "gcm.h"

// ���캯��
GroupLeader::GroupLeader():nextLeader(nullptr){}

GroupLeader::GroupLeader(GroupLeader* ano):nextLeader(ano){}

// ���ƹ��캯��
GroupLeader::GroupLeader(GroupLeader& ano)
{
    this->groupSize = ano.groupSize;
    this->nextLeader = ano.nextLeader;
    this->groups = ano.groups;
}

// ��ȡ��ǰ���С
int GroupLeader::size() const
{
    return groupSize;
}

// ��ȡһ�����п�Ŀ��
int GroupLeader::get()
{
    int t = groups.top();
    groups.pop();
    groupSize--;
    return t;
}

// ���������һ�����п�
bool GroupLeader::add(int id)
{
    if(groupSize >= groupCapacity) // ��ǰ������
        return false;
    else
    {
        groups.push(id);
        groupSize++;
        return true;
    }
}

//��������ĵ�ַ
GroupLeader* GroupLeader::self()
{
    return this;
}

//������һ���鳤���ַ
GroupLeader* GroupLeader::nextSelf()
{
    return nextLeader;
}

// ������һ���鳤��
bool GroupLeader::setNextLeader(GroupLeader* ano)
{
    nextLeader = ano;
    return true;
}

// ���һ�����п�
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

// ����һ�����ͷŵĿ�
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

// ��ȡ�ܿ��п���
int SuperGroup::size() const
{
    return groupTotalSize;
}

// ��ʼ������ջ
void SuperGroup::init()
{
    for(int i = 0; i < TOTAL_GROUP_SIZE / GROUP_SIZE; i++)
    {
        GroupLeader* t; // ������������
        if(i == 0) // �������������鳤�鸳����ǰ������
        {
            t = new GroupLeader;
            curGroup = t;
        }
        else
        {
            auto *t1 = new GroupLeader; // �����µ��鳤��
            t->setNextLeader(t1); // ���ӵ���һ�ֵ��鳤��
            t = t1; // ��������
        }
        for(int j = GROUP_SIZE; j >= 1 ; j--) // ��ÿһ�����ӿ��п�
        {
            t->add(i * GROUP_SIZE + j);
        }
    }
}

// ��ʾ��Ϣ
void SuperGroup::show()
{
    cout << "\n����������������������������������������������������\n";
    cout << "��ǰ����ջ����Ϊ" << curGroup->size() << endl;
    cout << "��ȡһ�����п���Ϊ" << getFreeBlock() << endl;
    cout << "\n����������������������������������������������������\n";
}
