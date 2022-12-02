// Copyright(c) 2015-present, Gabi Melman & FGEdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#ifndef FGEDLOG_HEADER_ONLY
#    include <FGEdlog/sinks/base_sink.h>
#endif

#include <FGEdlog/common.h>
#include <FGEdlog/pattern_formatter.h>

#include <memory>

template<typename Mutex>
FGEDLOG_INLINE FGEdlog::sinks::base_sink<Mutex>::base_sink()
    : formatter_{details::make_unique<FGEdlog::pattern_formatter>()}
{}

template<typename Mutex>
FGEDLOG_INLINE FGEdlog::sinks::base_sink<Mutex>::base_sink(std::unique_ptr<FGEdlog::formatter> formatter)
    : formatter_{std::move(formatter)}
{}

template<typename Mutex>
void FGEDLOG_INLINE FGEdlog::sinks::base_sink<Mutex>::log(const details::log_msg &msg)
{
    std::lock_guard<Mutex> lock(mutex_);
    sink_it_(msg);
}

template<typename Mutex>
void FGEDLOG_INLINE FGEdlog::sinks::base_sink<Mutex>::flush()
{
    std::lock_guard<Mutex> lock(mutex_);
    flush_();
}

template<typename Mutex>
void FGEDLOG_INLINE FGEdlog::sinks::base_sink<Mutex>::set_pattern(const std::string &pattern)
{
    std::lock_guard<Mutex> lock(mutex_);
    set_pattern_(pattern);
}

template<typename Mutex>
void FGEDLOG_INLINE FGEdlog::sinks::base_sink<Mutex>::set_formatter(std::unique_ptr<FGEdlog::formatter> sink_formatter)
{
    std::lock_guard<Mutex> lock(mutex_);
    set_formatter_(std::move(sink_formatter));
}

template<typename Mutex>
void FGEDLOG_INLINE FGEdlog::sinks::base_sink<Mutex>::set_pattern_(const std::string &pattern)
{
    set_formatter_(details::make_unique<FGEdlog::pattern_formatter>(pattern));
}

template<typename Mutex>
void FGEDLOG_INLINE FGEdlog::sinks::base_sink<Mutex>::set_formatter_(std::unique_ptr<FGEdlog::formatter> sink_formatter)
{
    formatter_ = std::move(sink_formatter);
}
