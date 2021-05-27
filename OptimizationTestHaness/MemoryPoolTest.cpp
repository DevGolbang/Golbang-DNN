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
//    cout << "TestPool 객체 1개의 메모리 : " << sizeof(TestPool) << " byte" << endl;
//    cout << "TestNomal 객체 1개의 메모리 : " << sizeof(TestNomal) << " byte" << endl;
//    cout << endl << endl;
//
//
//
//    cout << " 객체 1,000,000 번 생성/삭제 실험 " << endl;
//
//    /// 일반적인 객체 생성삭제 실험 ///
//    int t1 = GetTickCount();
//    for (long long i = 0; i < 1000000; ++i)
//    {
//        TestNomal* p = new TestNomal{};
//        delete p;
//    }
//
//    int t2 = GetTickCount() - t1;
//    cout << "일반 생성삭제 소요시간 : " << t2 << endl << endl;
//
//    /// 메모리풀로 객체 생성삭제 실험 ///
//    t1 = GetTickCount();
//    for (long long i = 0; i < 1000000; ++i)
//    {
//        TestPool* p = new TestPool{};
//        delete p;
//    }
//
//    t2 = GetTickCount() - t1;
//    cout << "메모리풀 이용 생성삭제 소요시간 : " << t2 << endl;
//
//
//    cout << endl << endl;
//    cout << " 결론 : 메모리풀을 이용하면 미리 메모리를 생성해두기 때문에 생성삭제 시간이 거의 소요되지 않는다." << endl;
//    cout << "        따라서 경우에 따라 게임 프로그래밍에 굉장히 유용할 수 있다. " << endl;
//
//
//
//    CMemoryPool<TestPool>::ReleasePool();
//    CMemoryPool<TestNomal>::ReleasePool();
//}