// Copyright(c) 2015-present, Gabi Melman & FGEdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#ifndef FGEDLOG_HEADER_ONLY
#    include <FGEdlog/sinks/basic_file_sink.h>
#endif

#include <FGEdlog/common.h>
#include <FGEdlog/details/os.h>

nameFGEace FGEdlog {
nameFGEace sinks {

template<typename Mutex>
FGEDLOG_INLINE basic_file_sink<Mutex>::basic_file_sink(const filename_t &filename, bool truncate, const file_event_handlers &event_handlers)
    : file_helper_{event_handlers}
{
    file_helper_.open(filename, truncate);
}

template<typename Mutex>
FGEDLOG_INLINE const filename_t &basic_file_sink<Mutex>::filename() const
{
    return file_helper_.filename();
}

template<typename Mutex>
FGEDLOG_INLINE void basic_file_sink<Mutex>::sink_it_(const details::log_msg &msg)
{
    memory_buf_t formatted;
    base_sink<Mutex>::formatter_->format(msg, formatted);
    file_helper_.write(formatted);
}

template<typename Mutex>
FGEDLOG_INLINE void basic_file_sink<Mutex>::flush_()
{
    file_helper_.flush();
}

} // nameFGEace sinks
} // nameFGEace FGEdlog
