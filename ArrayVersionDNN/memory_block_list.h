#pragma once

#include <iostream>
#include <cassert>
#include <memory>
#include <vector>

using namespace std;
typedef unsigned char UCHAR; //1바이트
typedef unsigned int UINT; // 4바이트


//저작권 : 일단 내껀 아님

template <class T, UINT MEMORY_BLOCK_SIZE = 1 >
class CMemoryPool {

private:
    static UCHAR* mPoolPointer;    // 메모리풀에 사용될 static 멤버 포인터
    static vector<UCHAR*> m_pointerForRelease;    // 블록 삭제하기위한 포인터 벡터
protected:
    ~CMemoryPool()
    {
    }

private:
    /// 메모리 할당 함수
    static void AllocBlock(UINT _size = MEMORY_BLOCK_SIZE)
    {
        //cout << "AllocBlock" << endl;

        // T블록으로 구분될 메모리 생성
        mPoolPointer = new UCHAR[sizeof(T) * _size];
        // 나중에 삭제하기위해 블록의 첫포인터 저장
        m_pointerForRelease.push_back(mPoolPointer);

        //curr은 첫 메모리를 가르킴 (앞에서 4바이트)
        UCHAR** curr = reinterpret_cast<UCHAR**>(mPoolPointer);
        //next는 첫 메모리를 가르킴 (앞에서 1바이트)
        UCHAR* next = mPoolPointer;

        for (int i = 0; i < _size - 1; ++i)
        {
            // next를 다음 블록으로 이동
            next += sizeof(T);
            //(curr은 UCHAR*형을 가르키는 포인터이므로 4바이트 블록 메모리의 주소를 가르키는데, 그 공간(*curr)에 next의 값(다음블록의 첫1바이트의 주소)를 대입한다)
            *curr = next;
            // next가 가르키고 있는 공간으로 curr이동
            curr = reinterpret_cast<UCHAR**>(next);
        }

        // 마지막 블록의 4바이트 공간은 NULL
        *curr = nullptr;
    }

public:

    // new 연산자 오버로딩
    /// new 연산자 오버로딩 약속 : 리턴은 void*로  매개변수는(size_t size)으로 크기정보가 바이트단위로 계산되어 전달 됨.
    static void* operator new(std::size_t _allocSize)
    {
        //할당된 바이트 출력
        //cout << _allocSize << endl;

        assert(sizeof(T) >= sizeof(UCHAR*));
        assert(sizeof(T) == _allocSize);

        //할당할 메모리가 없으면 메모리 블럭 생성
        if (!mPoolPointer)
            AllocBlock();

        // 리턴할 메모리의 주소
        UCHAR* returnPointer = mPoolPointer;
        // 리턴하는 블록 앞 4바이트에 들어있던 다음 블록의 주소를 mPoolPointer에 대입하여 mPoolPointer 이동
        mPoolPointer = *reinterpret_cast<UCHAR**>(returnPointer);

        return returnPointer;
    }


    // delete 연산자 오버로딩
    static void operator delete(void* deletePointer)
    {
        //cout << "delete" << endl;
        //지울 블록의 앞 4바이트에 현재 mPoolPointer의 주소를 넣어줌
        *reinterpret_cast<UCHAR**>(deletePointer) = mPoolPointer;
        // mPoolPointer 이동
        mPoolPointer = static_cast<UCHAR*>(deletePointer);
    }

    // 메모리풀에서 할당한 블록 메모리 소멸 (프로그램 종료시 호출되어야 함)
    static void ReleasePool()
    {
        for (auto i = m_pointerForRelease.begin(); i < m_pointerForRelease.end(); i++)
            delete[] * i;
    }
};


// static 멤버변수 초기화
template <class T, UINT MEMORY_DEFAULT_SIZE>
UCHAR* CMemoryPool<T, MEMORY_DEFAULT_SIZE>::mPoolPointer = nullptr;

template <class T, UINT MEMORY_DEFAULT_SIZE>
vector<UCHAR*> CMemoryPool<T, MEMORY_DEFAULT_SIZE>::m_pointerForRelease;
