#include <condition_variable>
#include <mutex>

namespace Semaphore
{

class CountingSemaphore final
{
public:
    explicit CountingSemaphore(int initialValue = 0);

    void signal();

    void wait();

private:
    std::mutex _mutex{};
    std::condition_variable _conditionVar{};
    int _value;
};

} // namespace Semaphore
