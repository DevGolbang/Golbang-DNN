#include <iostream>
#include "memory_block_list.h"
#include <time.h>
#include <Windows.h>



using namespace std;

class TestPool : public CMemoryPool<TestPool, 50>
{
private:
    int bbb[4567];
    double ccc[8910];
    long long ddd[100000];
public:
    char aaa[1234];
    TestPool()
    {
        strcpy_s(aaa, "HelloPool");
    }
};

class TestNomal {
private:
    char aaa[1234];
    int bbb[4567];
    double ccc[8910];
    long long ddd[100000];

};

//int main()
//{
//    cout << "TestPool ��ü 1���� �޸� : " << sizeof(TestPool) << " byte" << endl;
//    cout << "TestNomal ��ü 1���� �޸� : " << sizeof(TestNomal) << " byte" << endl;
//    cout << endl << endl;
//
//
//
//    cout << " ��ü 1,000,000 �� ����/���� ���� " << endl;
//
//    /// �Ϲ����� ��ü �������� ���� ///
//    int t1 = GetTickCount();
//    for (long long i = 0; i < 1000000; ++i)
//    {
//        TestNomal* p = new TestNomal{};
//        delete p;
//    }
//
//    int t2 = GetTickCount() - t1;
//    cout << "�Ϲ� �������� �ҿ�ð� : " << t2 << endl << endl;
//
//    /// �޸�Ǯ�� ��ü �������� ���� ///
//    t1 = GetTickCount();
//    for (long long i = 0; i < 1000000; ++i)
//    {
//        TestPool* p = new TestPool{};
//        delete p;
//    }
//
//    t2 = GetTickCount() - t1;
//    cout << "�޸�Ǯ �̿� �������� �ҿ�ð� : " << t2 << endl;
//
//
//    cout << endl << endl;
//    cout << " ��� : �޸�Ǯ�� �̿��ϸ� �̸� �޸𸮸� �����صα� ������ �������� �ð��� ���� �ҿ���� �ʴ´�." << endl;
//    cout << "        ���� ��쿡 ���� ���� ���α׷��ֿ� ������ ������ �� �ִ�. " << endl;
//
//
//
//    CMemoryPool<TestPool>::ReleasePool();
//    CMemoryPool<TestNomal>::ReleasePool();
//}