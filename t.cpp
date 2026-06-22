#include <thread>
#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

int run(const std::string leader, int cnt)
{
    for (int i = 0; i < cnt; ++i)
    {
        std::this_thread::sleep_for(1000ms);
        std::cerr << leader << i << "!\n";
    }
    return 0;
}

int main()
{
    std::thread t1(run, "T1: ", 15);
    std::thread t2(run, "T2: ", 20);

    std::this_thread::sleep_for(2500ms);

    t1.join();
    t2.join();
    std::cerr << "Done!\n";

    return 0;
}

