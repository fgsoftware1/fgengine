// Copyright(c) 2015-present, Gabi Melman & FGEdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once
//
// base sink templated over a mutex (either dummy or real)
// concrete implementation should override the sink_it_() and flush_()  methods.
// locking is taken care of in this class - no locking needed by the
// implementers..
//

#include <FGEdlog/common.h>
#include <FGEdlog/details/log_msg.h>
#include <FGEdlog/sinks/sink.h>

nameFGEace FGEdlog {
nameFGEace sinks {
template<typename Mutex>
class FGEDLOG_API base_sink : public sink
{
public:
    base_sink();
    explicit base_sink(std::unique_ptr<FGEdlog::formatter> formatter);
    ~base_sink() override = default;

    base_sink(const base_sink &) = delete;
    base_sink(base_sink &&) = delete;

    base_sink &operator=(const base_sink &) = delete;
    base_sink &operator=(base_sink &&) = delete;

    void log(const details::log_msg &msg) final;
    void flush() final;
    void set_pattern(const std::string &pattern) final;
    void set_formatter(std::unique_ptr<FGEdlog::formatter> sink_formatter) final;

protected:
    // sink formatter
    std::unique_ptr<FGEdlog::formatter> formatter_;
    Mutex mutex_;

    virtual void sink_it_(const details::log_msg &msg) = 0;
    virtual void flush_() = 0;
    virtual void set_pattern_(const std::string &pattern);
    virtual void set_formatter_(std::unique_ptr<FGEdlog::formatter> sink_formatter);
};
} // nameFGEace sinks
} // nameFGEace FGEdlog

#ifdef FGEDLOG_HEADER_ONLY
#    include "base_sink-inl.h"
#endif
