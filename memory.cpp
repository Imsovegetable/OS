//
// Created by �ɳ����� on 2021/5/26.
//
#include "memory.h"

// ���캯��
NormalIndex::NormalIndex(int sign):sign(sign){}

// ��ȡ��n������
int NormalIndex::getIndex(int n)
{
    if(n >= indexSize || n < 0) // n������Χ
        return -1;
    else
        return indexes[n];
}

// ��Ӵ��̿��Ϊid��������
bool NormalIndex::addIndex(int id)
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
int NormalIndex::size() const
{
    return indexSize;
}

// ����������ɾ��n������
bool NormalIndex::dropIndex(int n)
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
bool NormalIndex::dropIndex()
{
    if(indexSize > 0)
    {
        indexes.pop_back();
        indexSize--;
        return true;
    }
    return false;
}

// ���������л�ȡ��n����һ��������
NormalIndex& NormalIndex::getNxtIndex(int n)
{
    return indexTables[n];
}

// ���һ����һ��������
bool NormalIndex::addNxtIndex()
{
    if(indexSize >= indexCapacity)
        return false;
    else {
        auto *t = new NormalIndex(sign - 1);
        indexTables.push_back(*t);
        indexSize++;
        return true;
    }
}

// ɾ����n����һ��������
bool NormalIndex::dropNxtIndex(int n)
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
bool NormalIndex::dropNxtIndex()
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
int NormalIndex::check() const
{
    return sign;
}

// ��ʾ������Ϣ
void NormalIndex::show()
{
    cout << "\n";
    for(int i = 0; i < indexSize; i++)
        cout << indexes[i] << " ";
    cout << "\n";
}

// ���캯��
MixIndex::MixIndex(): oneIndirectIndex(0), twoIndirectIndex(1), threeIndirectIndex(2){}

// ���һ������
bool MixIndex::addIndex(int id)
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
bool MixIndex::addDirectIndex(int id)
{
    indexes.push_back(id);
    indexSize++;
    return true;
}

// ���һ�μ������
bool MixIndex::addOneIndirectIndex(int id)
{
    oneIndirectIndex.addIndex(id);
    indexSize++;
    return true;
}

// ��Ӷ��μ������
bool MixIndex::addTwoIndirectIndex(int id)
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
bool MixIndex::addThreeIndirectIndex(int id)
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
int MixIndex::size() const
{
    return indexSize;
}

// չʾ��Ϣ
void MixIndex::show()
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
bool MixIndex::dropIndex()
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
bool MixIndex::dropDirectIndex()
{
    indexes.pop_back();
    indexSize--;
    return true;
}

// ɾ��һ�μ������
bool MixIndex::dropOneInDirectIndex()
{
    oneIndirectIndex.dropIndex();
    indexSize--;
    return true;
}

// ɾ�����μ������
bool MixIndex::dropTwoInDirectIndex()
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
bool MixIndex::dropThreeInDirectIndex()
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