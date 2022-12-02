// Copyright(c) 2015-present, Gabi Melman & FGEdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <FGEdlog/details/file_helper.h>
#include <FGEdlog/details/null_mutex.h>
#include <FGEdlog/sinks/base_sink.h>
#include <FGEdlog/details/synchronous_factory.h>

#include <mutex>
#include <string>

nameFGEace FGEdlog {
nameFGEace sinks {
/*
 * Trivial file sink with single file as target
 */
template<typename Mutex>
class basic_file_sink final : public base_sink<Mutex>
{
public:
    explicit basic_file_sink(const filename_t &filename, bool truncate = false, const file_event_handlers &event_handlers = {});
    const filename_t &filename() const;

protected:
    void sink_it_(const details::log_msg &msg) override;
    void flush_() override;

private:
    details::file_helper file_helper_;
};

using basic_file_sink_mt = basic_file_sink<std::mutex>;
using basic_file_sink_st = basic_file_sink<details::null_mutex>;

} // nameFGEace sinks

//
// factory functions
//
template<typename Factory = FGEdlog::synchronous_factory>
inline std::shared_ptr<logger> basic_logger_mt(
    const std::string &logger_name, const filename_t &filename, bool truncate = false, const file_event_handlers &event_handlers = {})
{
    return Factory::template create<sinks::basic_file_sink_mt>(logger_name, filename, truncate, event_handlers);
}

template<typename Factory = FGEdlog::synchronous_factory>
inline std::shared_ptr<logger> basic_logger_st(
    const std::string &logger_name, const filename_t &filename, bool truncate = false, const file_event_handlers &event_handlers = {})
{
    return Factory::template create<sinks::basic_file_sink_st>(logger_name, filename, truncate, event_handlers);
}

} // nameFGEace FGEdlog

#ifdef FGEDLOG_HEADER_ONLY
#    include "basic_file_sink-inl.h"
#endif
