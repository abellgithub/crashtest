#include <thread>
#include <chrono>
#include <iostream>

#include "Stackwalker.h"

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

    class MyStackWalker : public StackWalker
    {
    protected:
        virtual void OnOutput(LPCSTR text)
        {
            std::cerr << std::string(text) << "!\n";
            StackWalker::OnOutput(text);
        }
    };

    MyStackWalker s1;
    s1.ShowCallstack(t1.native_handle());

    std::cerr << "Done stackwalk!\n";

    t1.join();
    t2.join();

    std::cerr << "Done!\n";

    return 0;
}

