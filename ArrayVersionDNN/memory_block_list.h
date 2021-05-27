#pragma once

#include <iostream>
#include <cassert>
#include <memory>
#include <vector>

using namespace std;
typedef unsigned char UCHAR; //1����Ʈ
typedef unsigned int UINT; // 4����Ʈ


//���۱� : �ϴ� ���� �ƴ�

template <class T, UINT MEMORY_BLOCK_SIZE = 1 >
class CMemoryPool {

private:
    static UCHAR* mPoolPointer;    // �޸�Ǯ�� ���� static ��� ������
    static vector<UCHAR*> m_pointerForRelease;    // ��� �����ϱ����� ������ ����
protected:
    ~CMemoryPool()
    {
    }

private:
    /// �޸� �Ҵ� �Լ�
    static void AllocBlock(UINT _size = MEMORY_BLOCK_SIZE)
    {
        //cout << "AllocBlock" << endl;

        // T������� ���е� �޸� ����
        mPoolPointer = new UCHAR[sizeof(T) * _size];
        // ���߿� �����ϱ����� ����� ù������ ����
        m_pointerForRelease.push_back(mPoolPointer);

        //curr�� ù �޸𸮸� ����Ŵ (�տ��� 4����Ʈ)
        UCHAR** curr = reinterpret_cast<UCHAR**>(mPoolPointer);
        //next�� ù �޸𸮸� ����Ŵ (�տ��� 1����Ʈ)
        UCHAR* next = mPoolPointer;

        for (int i = 0; i < _size - 1; ++i)
        {
            // next�� ���� ������� �̵�
            next += sizeof(T);
            //(curr�� UCHAR*���� ����Ű�� �������̹Ƿ� 4����Ʈ ��� �޸��� �ּҸ� ����Ű�µ�, �� ����(*curr)�� next�� ��(��������� ù1����Ʈ�� �ּ�)�� �����Ѵ�)
            *curr = next;
            // next�� ����Ű�� �ִ� �������� curr�̵�
            curr = reinterpret_cast<UCHAR**>(next);
        }

        // ������ ����� 4����Ʈ ������ NULL
        *curr = nullptr;
    }

public:

    // new ������ �����ε�
    /// new ������ �����ε� ��� : ������ void*��  �Ű�������(size_t size)���� ũ�������� ����Ʈ������ ���Ǿ� ���� ��.
    static void* operator new(std::size_t _allocSize)
    {
        //�Ҵ�� ����Ʈ ���
        //cout << _allocSize << endl;

        assert(sizeof(T) >= sizeof(UCHAR*));
        assert(sizeof(T) == _allocSize);

        //�Ҵ��� �޸𸮰� ������ �޸� �� ����
        if (!mPoolPointer)
            AllocBlock();

        // ������ �޸��� �ּ�
        UCHAR* returnPointer = mPoolPointer;
        // �����ϴ� ��� �� 4����Ʈ�� ����ִ� ���� ����� �ּҸ� mPoolPointer�� �����Ͽ� mPoolPointer �̵�
        mPoolPointer = *reinterpret_cast<UCHAR**>(returnPointer);

        return returnPointer;
    }


    // delete ������ �����ε�
    static void operator delete(void* deletePointer)
    {
        //cout << "delete" << endl;
        //���� ����� �� 4����Ʈ�� ���� mPoolPointer�� �ּҸ� �־���
        *reinterpret_cast<UCHAR**>(deletePointer) = mPoolPointer;
        // mPoolPointer �̵�
        mPoolPointer = static_cast<UCHAR*>(deletePointer);
    }

    // �޸�Ǯ���� �Ҵ��� ��� �޸� �Ҹ� (���α׷� ����� ȣ��Ǿ�� ��)
    static void ReleasePool()
    {
        for (auto i = m_pointerForRelease.begin(); i < m_pointerForRelease.end(); i++)
            delete[] * i;
    }
};


// static ������� �ʱ�ȭ
template <class T, UINT MEMORY_DEFAULT_SIZE>
UCHAR* CMemoryPool<T, MEMORY_DEFAULT_SIZE>::mPoolPointer = nullptr;

template <class T, UINT MEMORY_DEFAULT_SIZE>
vector<UCHAR*> CMemoryPool<T, MEMORY_DEFAULT_SIZE>::m_pointerForRelease;
