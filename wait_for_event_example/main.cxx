#include <thread>
#include <iostream>
#include <wait_for_event.hxx>

wfe::WaitForEvent event;

void thread_runner(void)
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        event.notify_all();
    }
}

int main(int argc, char const* argv[])
{
    std::thread t{ thread_runner };
    while (true)
    {
        auto return_status = event.wait_for(std::chrono::seconds(1));
        if (return_status == wfe::WaitForEventStatus::Timeout)
        {
            std::cout << "WaitForEventStatus::Timeout\n";
        }
        else if (return_status == wfe::WaitForEventStatus::NoTimeout)
        {
            std::cout << "WaitForEventStatus::NoTimeout\n";
        }
    }

    return 0;
}
