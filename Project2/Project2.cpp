#include <iostream>
#include <future>

void for_print_char(char c) {
    for (int i = 0; i < 70; i++)
        printf("%c번 Thread : %d\n", c, i);
}
void for_print_int(int c) {
    for (int i = 0; i < 70; i++)
        printf("%d번 Thread : %d\n", c, i);
}
int main() {
    //std::future<void> a = std::async(for_print_char, 'a');
    //a.wait();
    //std::future<void> b = std::async(for_print_char, 'b');
    //b.wait();
    //std::future<void> c = std::async(for_print_char, 'c');
    //c.wait();
    //
    
    std::future<void> d[8];
    for (int i = 0; i < 8; i++) {
        d[i] = std::async(for_print_int, i);
        //d[i].wait();
    }
    for (int i = 0; i < 8; i++) {
       // d[i].wait();
    }
    printf("안녕하심꽈");
    //b.get();
    return 0;
}