#include <thread>
#include <iostream>
template < typename T2 >
class bar{
public:
    void foo(int a,int b, int c) {
        std::cout << "hello from member function" << std::endl;
    }
    void foo() {
        std::thread t[8];
        for (int i = 0; i < 8; i++) {
            t[i] = std::thread(&bar::foo, this,1,2,3);
        }
        for (int i = 0; i < 8; i++) {
            t[i].join();
        }

    }
};

int main()
{
    bar<int> bb = bar<int>();
    bb.foo();
}