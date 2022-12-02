//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//

//
// bench.cpp : FGEdlog benchmarks
//
#include "FGEdlog/FGEdlog.h"
#include "FGEdlog/sinks/basic_file_sink.h"
#include "FGEdlog/sinks/daily_file_sink.h"
#include "FGEdlog/sinks/null_sink.h"
#include "FGEdlog/sinks/rotating_file_sink.h"

#if defined(FGEDLOG_USE_STD_FORMAT)
#    include <format>
#elif defined(FGEDLOG_FMT_EXTERNAL)
#    include <fmt/format.h>
#else
#    include "FGEdlog/fmt/bundled/format.h"
#endif

#include "utils.h"
#include <atomic>
#include <cstdlib> // EXIT_FAILURE
#include <memory>
#include <string>
#include <thread>

void bench(int howmany, std::shared_ptr<FGEdlog::logger> log);
void bench_mt(int howmany, std::shared_ptr<FGEdlog::logger> log, size_t thread_count);

// void bench_default_api(int howmany, std::shared_ptr<FGEdlog::logger> log);
// void bench_c_string(int howmany, std::shared_ptr<FGEdlog::logger> log);

static const size_t file_size = 30 * 1024 * 1024;
static const size_t rotating_files = 5;
static const int max_threads = 1000;

void bench_threaded_logging(size_t threads, int iters)
{
    FGEdlog::info("**************************************************************");
    FGEdlog::info(FGEdlog::fmt_lib::format(std::locale("en_US.UTF-8"), "Multi threaded: {:L} threads, {:L} messages", threads, iters));
    FGEdlog::info("**************************************************************");

    auto basic_mt = FGEdlog::basic_logger_mt("basic_mt", "logs/basic_mt.log", true);
    bench_mt(iters, std::move(basic_mt), threads);
    auto basic_mt_tracing = FGEdlog::basic_logger_mt("basic_mt/backtrace-on", "logs/basic_mt.log", true);
    basic_mt_tracing->enable_backtrace(32);
    bench_mt(iters, std::move(basic_mt_tracing), threads);

    FGEdlog::info("");
    auto rotating_mt = FGEdlog::rotating_logger_mt("rotating_mt", "logs/rotating_mt.log", file_size, rotating_files);
    bench_mt(iters, std::move(rotating_mt), threads);
    auto rotating_mt_tracing = FGEdlog::rotating_logger_mt("rotating_mt/backtrace-on", "logs/rotating_mt.log", file_size, rotating_files);
    rotating_mt_tracing->enable_backtrace(32);
    bench_mt(iters, std::move(rotating_mt_tracing), threads);

    FGEdlog::info("");
    auto daily_mt = FGEdlog::daily_logger_mt("daily_mt", "logs/daily_mt.log");
    bench_mt(iters, std::move(daily_mt), threads);
    auto daily_mt_tracing = FGEdlog::daily_logger_mt("daily_mt/backtrace-on", "logs/daily_mt.log");
    daily_mt_tracing->enable_backtrace(32);
    bench_mt(iters, std::move(daily_mt_tracing), threads);

    FGEdlog::info("");
    auto empty_logger = std::make_shared<FGEdlog::logger>("level-off");
    empty_logger->set_level(FGEdlog::level::off);
    bench(iters, empty_logger);
    auto empty_logger_tracing = std::make_shared<FGEdlog::logger>("level-off/backtrace-on");
    empty_logger_tracing->set_level(FGEdlog::level::off);
    empty_logger_tracing->enable_backtrace(32);
    bench(iters, empty_logger_tracing);
}

void bench_single_threaded(int iters)
{
    FGEdlog::info("**************************************************************");
    FGEdlog::info(FGEdlog::fmt_lib::format(std::locale("en_US.UTF-8"), "Single threaded: {} messages", iters));
    FGEdlog::info("**************************************************************");

    auto basic_st = FGEdlog::basic_logger_st("basic_st", "logs/basic_st.log", true);
    bench(iters, std::move(basic_st));

    auto basic_st_tracing = FGEdlog::basic_logger_st("basic_st/backtrace-on", "logs/basic_st.log", true);
    bench(iters, std::move(basic_st_tracing));

    FGEdlog::info("");
    auto rotating_st = FGEdlog::rotating_logger_st("rotating_st", "logs/rotating_st.log", file_size, rotating_files);
    bench(iters, std::move(rotating_st));
    auto rotating_st_tracing = FGEdlog::rotating_logger_st("rotating_st/backtrace-on", "logs/rotating_st.log", file_size, rotating_files);
    rotating_st_tracing->enable_backtrace(32);
    bench(iters, std::move(rotating_st_tracing));

    FGEdlog::info("");
    auto daily_st = FGEdlog::daily_logger_st("daily_st", "logs/daily_st.log");
    bench(iters, std::move(daily_st));
    auto daily_st_tracing = FGEdlog::daily_logger_st("daily_st/backtrace-on", "logs/daily_st.log");
    daily_st_tracing->enable_backtrace(32);
    bench(iters, std::move(daily_st_tracing));

    FGEdlog::info("");
    auto empty_logger = std::make_shared<FGEdlog::logger>("level-off");
    empty_logger->set_level(FGEdlog::level::off);
    bench(iters, empty_logger);

    auto empty_logger_tracing = std::make_shared<FGEdlog::logger>("level-off/backtrace-on");
    empty_logger_tracing->set_level(FGEdlog::level::off);
    empty_logger_tracing->enable_backtrace(32);
    bench(iters, empty_logger_tracing);
}

int main(int argc, char *argv[])
{
    FGEdlog::set_automatic_registration(false);
    FGEdlog::default_logger()->set_pattern("[%^%l%$] %v");
    int iters = 250000;
    size_t threads = 4;
    try
    {

        if (argc > 1)
        {
            iters = std::stoi(argv[1]);
        }
        if (argc > 2)
        {
            threads = std::stoul(argv[2]);
        }

        if (threads > max_threads)
        {
            throw std::runtime_error(FGEdlog::fmt_lib::format("Number of threads exceeds maximum({})", max_threads));
        }

        bench_single_threaded(iters);
        bench_threaded_logging(1, iters);
        bench_threaded_logging(threads, iters);
    }
    catch (std::exception &ex)
    {
        FGEdlog::error(ex.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void bench(int howmany, std::shared_ptr<FGEdlog::logger> log)
{
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;

    auto start = high_resolution_clock::now();
    for (auto i = 0; i < howmany; ++i)
    {
        log->info("Hello logger: msg number {}", i);
    }

    auto delta = high_resolution_clock::now() - start;
    auto delta_d = duration_cast<duration<double>>(delta).count();

    FGEdlog::info(FGEdlog::fmt_lib::format(
        std::locale("en_US.UTF-8"), "{:<30} Elapsed: {:0.2f} secs {:>16L}/sec", log->name(), delta_d, int(howmany / delta_d)));
    FGEdlog::drop(log->name());
}

void bench_mt(int howmany, std::shared_ptr<FGEdlog::logger> log, size_t thread_count)
{
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;

    std::vector<std::thread> threads;
    threads.reserve(thread_count);
    auto start = high_resolution_clock::now();
    for (size_t t = 0; t < thread_count; ++t)
    {
        threads.emplace_back([&]() {
            for (int j = 0; j < howmany / static_cast<int>(thread_count); j++)
            {
                log->info("Hello logger: msg number {}", j);
            }
        });
    }

    for (auto &t : threads)
    {
        t.join();
    };

    auto delta = high_resolution_clock::now() - start;
    auto delta_d = duration_cast<duration<double>>(delta).count();
    FGEdlog::info(FGEdlog::fmt_lib::format(
        std::locale("en_US.UTF-8"), "{:<30} Elapsed: {:0.2f} secs {:>16L}/sec", log->name(), delta_d, int(howmany / delta_d)));
    FGEdlog::drop(log->name());
}

/*
void bench_default_api(int howmany, std::shared_ptr<FGEdlog::logger> log)
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration;
    using std::chrono::duration_cast;

    auto orig_default = FGEdlog::default_logger();
    FGEdlog::set_default_logger(log);
    auto start = high_resolution_clock::now();
    for (auto i = 0; i < howmany; ++i)
    {
        FGEdlog::info("Hello logger: msg number {}", i);
    }

    auto delta = high_resolution_clock::now() - start;
    auto delta_d = duration_cast<duration<double>>(delta).count();
    FGEdlog::drop(log->name());
    FGEdlog::set_default_logger(std::move(orig_default));
    FGEdlog::info("{:<30} Elapsed: {:0.2f} secs {:>16}/sec", log->name(), delta_d, int(howmany / delta_d));
}

void bench_c_string(int howmany, std::shared_ptr<FGEdlog::logger> log)
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration;
    using std::chrono::duration_cast;

    const char *msg = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum pharetra metus cursus "
                      "lacus placerat congue. Nulla egestas, mauris a tincidunt tempus, enim lectus volutpat mi, eu consequat sem "
                      "libero nec massa. In dapibus ipsum a diam rhoncus gravida. Etiam non dapibus eros. Donec fringilla dui sed "
                      "augue pretium, nec scelerisque est maximus. Nullam convallis, sem nec blandit maximus, nisi turpis ornare "
                      "nisl, sit amet volutpat neque massa eu odio. Maecenas malesuada quam ex, posuere congue nibh turpis duis.";

    auto orig_default = FGEdlog::default_logger();
    FGEdlog::set_default_logger(log);
    auto start = high_resolution_clock::now();
    for (auto i = 0; i < howmany; ++i)
    {
        FGEdlog::log(FGEdlog::level::info, msg);
    }

    auto delta = high_resolution_clock::now() - start;
    auto delta_d = duration_cast<duration<double>>(delta).count();
    FGEdlog::drop(log->name());
    FGEdlog::set_default_logger(std::move(orig_default));
    FGEdlog::info("{:<30} Elapsed: {:0.2f} secs {:>16}/sec", log->name(), delta_d, int(howmany / delta_d));
}

*/