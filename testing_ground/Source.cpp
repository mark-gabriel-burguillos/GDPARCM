#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void foo()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << "Message from foo\n";
}

int main()
{
    std::thread t1(foo);

    std::cout << "Message from main thread before join\n";
    //t1.detach();
    std::cout << "Message from main thread after join\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(6000));
}