//
// Created by �ɳ����� on 2021/5/25.
//
#include <bits/stdc++.h>
#include "GODNING.h"

#ifndef OS_MEMORY_H
#define OS_MEMORY_H

using namespace std;

// ��ͨ������
class NormalIndex{
private:
    const int indexCapacity = IDXT_SIZE;
    const int sign;
    int indexSize = 0;
    vector<int> indexes;
    vector<NormalIndex> indexTables;

public:
    NormalIndex(int sign):sign(sign){}

    //��Ϊĩ�������Ĺ���

    // ��ȡ��n������
    int getIndex(int n)
    {
        if(n >= indexSize || n < 0) // n������Χ
            return -1;
        else
            return indexes[n];
    }
    // ��Ӵ��̿��Ϊid��������
    bool addIndex(int id)
    {
        if(id < 0 || indexSize >= indexCapacity) // id������Χ������������
            return false;
        else
        {
            indexes.push_back(id);
            indexSize++;
            return true;
        }
    }
    // ��ȡ������������������
    int size()
    {
        return indexSize;
    }
    // ����������ɾ��n������
    bool dropIndex(int n)
    {
        if(n > indexSize || n <= 0) // n������Χ
            return false;
        else
        {
            for(int i = indexSize - 1; i > indexSize - 1 - n; i--) // ɾ����n������������
                indexes.pop_back();
            indexSize -= n;
            return true;
        }
    }
    // ɾ�����һ������
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

    //��Ϊ�м������Ĺ���

    // ���������л�ȡ��n����һ��������
    NormalIndex& getNxtIndex(int n)
    {
        return indexTables[n];
    }
    // ���һ����һ��������
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
    // ɾ����n����һ��������
    bool dropNxtIndex(int n)
    {
        if(n > indexSize || n <= 0) // n������Χ
            return false;
        else
        {
            for(int i = indexSize - 1; i > indexSize - 1 - n; i--) // ɾ����n������������
                indexTables.pop_back();
            indexSize -= n;
            return true;
        }
    }
    // ɾ�����һ����һ��������
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
    // ��ѯsignֵ
    int check()
    {
        return sign;
    }
    // ��ʾ������Ϣ
    void show()
    {
        cout << "\n";
        for(int i = 0; i < indexSize; i++)
            cout << indexes[i] << " ";
        cout << "\n";
    }
};


// ���������
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

    // ���һ������
    bool addIndex(int id)
    {
        if(indexSize >= indexCapacity || id < 0) // �����Ѿ����˻���id������Χ
            return false;
        else
        {
            if(indexSize < BASIC_IDX) // ֱ������
                return addDirectIndex(id);
            else if(indexSize >= BASIC_IDX && indexSize < BASIC_IDX + IDXT_SIZE) // һ�μ������
                return addOneIndirectIndex(id);
            else if(indexSize >= BASIC_IDX + IDXT_SIZE && indexSize < BASIC_IDX + IDXT_SIZE + ONE_IDXT_SIZE) // ���μ������
                return addTwoIndirectIndex(id);
            else if(indexSize >= BASIC_IDX + IDXT_SIZE + ONE_IDXT_SIZE && indexSize < MIX_IDXT_SIZE) // ���μ������
                return addThreeIndirectIndex(id);
            else
                return false;
        }
    }
    // ���ֱ������
    bool addDirectIndex(int id)
    {
        indexes.push_back(id);
        indexSize++;
        return true;
    }
    // ���һ�μ������
    bool addOneIndirectIndex(int id)
    {
        oneIndirectIndex.addIndex(id);
        indexSize++;
        return true;
    }
    // ��Ӷ��μ������
    bool addTwoIndirectIndex(int id)
    {
        // ���㳬��ǰ����������������
        int n = indexSize - BASIC_IDX - IDXT_SIZE;
        if(n % IDXT_SIZE == 0) //��������ǰһ�����μ�ַ������
            twoIndirectIndex.addNxtIndex(); // �½�һ��������

        //��õ�ǰδ���Ķ��μ�ַ������
        NormalIndex &t = twoIndirectIndex.getNxtIndex(n / IDXT_SIZE);
        t.addIndex(id);
        indexSize++;
        return true; // �������
    }
    // ������μ������
    bool addThreeIndirectIndex(int id)
    {
        // ���㳬��ǰ����������������
        int n = indexSize - BASIC_IDX - IDXT_SIZE - ONE_IDXT_SIZE;
        if(n % ONE_IDXT_SIZE == 0) // ��������ǰһ�����μ�ַ������
            threeIndirectIndex.addNxtIndex(); // �½�һ�����μ�ַ������

        // ��õ�ǰδ���Ķ��μ�ַ������
        NormalIndex &t = threeIndirectIndex.getNxtIndex(n / ONE_IDXT_SIZE);
        if(n % IDXT_SIZE == 0) // ��������һ�����μ�ַ������
            t.addNxtIndex(); // �½�һ�����μ�ַ������

        // ��õ�ǰδ�������μ�ַ������
        NormalIndex &nxt = t.getNxtIndex((n % ONE_IDXT_SIZE) / IDXT_SIZE);
        nxt.addIndex(id);
        indexSize++;
        return true; // �������
    }
    // ������������
    int size()
    {
        return indexSize;
    }
    // չʾ��Ϣ
    void show()
    {
        cout << "������������������������������������������������������������\n";
        cout << "ֱ����������\n";
        for(int i = 0; i < min(indexSize, BASIC_IDX); i++)
            cout << indexes[i] << " ";
        cout << "\n";
        cout << "һ�μ����������";
        if(indexSize >= BASIC_IDX)
        {
            oneIndirectIndex.show();
        }
        cout << "���μ����������";
        if(indexSize >= BASIC_IDX + IDXT_SIZE)
        {
            int n = twoIndirectIndex.size();
            for(int i = 0; i < n; i++)
                twoIndirectIndex.getNxtIndex(i).show();
        }
        cout << "���μ����������";
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
        cout << "\n������������������������������������������������������������\n";
    }
    // ɾ��һ������
    bool dropIndex()
    {
        if(indexSize <= 0)
            return false;
        else if(indexSize <= BASIC_IDX) // ֱ������
            return dropDirectIndex();
        else if(indexSize <= BASIC_IDX + IDXT_SIZE) // һ�μ������
            return dropOneInDirectIndex();
        else if(indexSize <= BASIC_IDX + IDXT_SIZE + ONE_IDXT_SIZE) // ���μ������
            return dropTwoInDirectIndex();
        else
            return dropThreeInDirectIndex(); // ���μ������
    }
    // ɾ��ֱ������
    bool dropDirectIndex()
    {
        indexes.pop_back();
        indexSize--;
        return true;
    }
    // ɾ��һ�μ������
    bool dropOneInDirectIndex()
    {
        oneIndirectIndex.dropIndex();
        indexSize--;
        return true;
    }
    // ɾ�����μ������
    bool dropTwoInDirectIndex()
    {
        // ���㳬��ǰ�����ֵ���������
        int n = indexSize - BASIC_IDX - IDXT_SIZE - 1; //����ļ�һ�ǳ���Ҫ����Ϊsize�Ǵ�1��ʼ�ģ��±����Ǵ�0��ʼ�����³���ʱ������һ����
        // �ҵ���Ӧ�Ķ��μ�ַ������
        twoIndirectIndex.getNxtIndex(n / IDXT_SIZE).dropIndex();
        indexSize--;
        // �˴�n�ĺ���Ӧ�������������±꣬���Ҫ�Ѽ�һ��������
        if((n + 1) % IDXT_SIZE == 1) // ���ɾ���������Ƕ��μ�ַ����������һ������
            twoIndirectIndex.dropNxtIndex(); // ��������Ҳɾ��
        return true;
    }
    // ɾ�����μ������
    bool dropThreeInDirectIndex()
    {
        // ���㳬��ǰ�����ֵ���������
        int n = indexSize - BASIC_IDX - IDXT_SIZE - ONE_IDXT_SIZE - 1;// ͬ�ϣ�һ��Ҫ��һ
        // �ҵ���Ӧ�����μ�ַ������
        threeIndirectIndex.getNxtIndex(n / ONE_IDXT_SIZE).getNxtIndex((n % ONE_IDXT_SIZE) / IDXT_SIZE).dropIndex();
        indexSize--;
        // �˴�n�ĺ���Ӧ�������������±꣬���Ҫ�Ѽ�һ��������
        if(((n + 1) % ONE_IDXT_SIZE) % IDXT_SIZE == 1) // ���ɾ�������������μ�ַ����������һ������
            threeIndirectIndex.getNxtIndex(n / ONE_IDXT_SIZE).dropNxtIndex(); // ��������μ�ַ������Ҳɾ��
        // �˴�n�ĺ���Ӧ�������������±꣬���Ҫ�Ѽ�һ��������
        if((n + 1) % ONE_IDXT_SIZE == 1) // ���ɾ���������Ƕ��μ�ַ����������һ������
            threeIndirectIndex.dropNxtIndex(); // ��������μ�ַ������Ҳɾ��
        return true;
    }
};



#endif //OS_MEMORY_H
