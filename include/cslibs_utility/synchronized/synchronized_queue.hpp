#ifndef CSLIBS_UTILITY_SYNCHRONIZED_QUEUE_HPP
#define CSLIBS_UTILITY_SYNCHRONIZED_QUEUE_HPP

#include <queue>
#include <mutex>

namespace cslibs_utility {
namespace synchronized {
template<typename _Tp, typename _Sequence = std::deque<_Tp>>
class queue
{
public:
    using mutex_t = std::mutex;
    using lock_t  = std::unique_lock<mutex_t>;

    inline queue() = default;

    inline bool empty() const
    {
        lock_t l(mutex_);
        return q_.empty();
    }

    inline bool hasElements() const
    {
        return !empty();
    }

    inline std::size_t size() const
    {
        lock_t l(mutex_);
        return q_.size();
    }

    inline _Tp pop()
    {
        lock_t l(mutex_);
        _Tp t = q_.front();
        q_.pop();
        return t;
    }

    inline _Tp const & top() const
    {
        lock_t l(mutex_);
        return q_.front();
    }

    inline void emplace(const _Tp &t)
    {
        lock_t l(mutex_);
        q_.emplace(t);
    }

    inline void push(const _Tp &t)
    {
        lock_t l(mutex_);
        q_.push(t);
    }

private:
    mutable mutex_t mutex_;
    std::queue<_Tp, _Sequence> q_;
};
}
}


#endif // CSLIBS_UTILITY_SYNCHRONIZED_QUEUE_HPP
