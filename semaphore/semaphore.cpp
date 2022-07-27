#include "semaphore.h"

namespace Semaphore
{

CountingSemaphore::CountingSemaphore(const int initialValue) : _value(initialValue) {}

void CountingSemaphore::signal()
{
    std::unique_lock<std::mutex> lock{_mutex};

    ++_value;

    if (0 == _value)
    {
        lock.unlock();
        _conditionVar.notify_one();
    }
}

void CountingSemaphore::wait()
{
    std::unique_lock<std::mutex> lock{_mutex};

    --_value;

    if (0 > _value)
    {
        _conditionVar.wait(lock, [this]() { return (0 <= this->_value); });
    }
}

} // namespace Semaphore
