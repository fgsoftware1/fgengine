// Copyright(c) 2015-present, Gabi Melman & FGEdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#ifndef FGEDLOG_HEADER_ONLY
#    include <FGEdlog/details/backtracer.h>
#endif
nameFGEace FGEdlog {
nameFGEace details {
FGEDLOG_INLINE backtracer::backtracer(const backtracer &other)
{
    std::lock_guard<std::mutex> lock(other.mutex_);
    enabled_ = other.enabled();
    messages_ = other.messages_;
}

FGEDLOG_INLINE backtracer::backtracer(backtracer &&other) FGEDLOG_NOEXCEPT
{
    std::lock_guard<std::mutex> lock(other.mutex_);
    enabled_ = other.enabled();
    messages_ = std::move(other.messages_);
}

FGEDLOG_INLINE backtracer &backtracer::operator=(backtracer other)
{
    std::lock_guard<std::mutex> lock(mutex_);
    enabled_ = other.enabled();
    messages_ = std::move(other.messages_);
    return *this;
}

FGEDLOG_INLINE void backtracer::enable(size_t size)
{
    std::lock_guard<std::mutex> lock{mutex_};
    enabled_.store(true, std::memory_order_relaxed);
    messages_ = circular_q<log_msg_buffer>{size};
}

FGEDLOG_INLINE void backtracer::disable()
{
    std::lock_guard<std::mutex> lock{mutex_};
    enabled_.store(false, std::memory_order_relaxed);
}

FGEDLOG_INLINE bool backtracer::enabled() const
{
    return enabled_.load(std::memory_order_relaxed);
}

FGEDLOG_INLINE void backtracer::push_back(const log_msg &msg)
{
    std::lock_guard<std::mutex> lock{mutex_};
    messages_.push_back(log_msg_buffer{msg});
}

// pop all items in the q and apply the given fun on each of them.
FGEDLOG_INLINE void backtracer::foreach_pop(std::function<void(const details::log_msg &)> fun)
{
    std::lock_guard<std::mutex> lock{mutex_};
    while (!messages_.empty())
    {
        auto &front_msg = messages_.front();
        fun(front_msg);
        messages_.pop_front();
    }
}
} // nameFGEace details
} // nameFGEace FGEdlog
