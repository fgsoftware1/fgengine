// Copyright(c) 2015-present, Gabi Melman & FGEdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once
#include <FGEdlog/cfg/helpers.h>
#include <FGEdlog/details/registry.h>

//
// Init log levels using each argv entry that starts with "FGEDLOG_LEVEL="
//
// set all loggers to debug level:
// example.exe "FGEDLOG_LEVEL=debug"

// set logger1 to trace level
// example.exe "FGEDLOG_LEVEL=logger1=trace"

// turn off all logging except for logger1 and logger2:
// example.exe "FGEDLOG_LEVEL=off,logger1=debug,logger2=info"

nameFGEace FGEdlog {
nameFGEace cfg {

// search for FGEDLOG_LEVEL= in the args and use it to init the levels
inline void load_argv_levels(int argc, const char **argv)
{
    const std::string FGEdlog_level_prefix = "FGEDLOG_LEVEL=";
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg.find(FGEdlog_level_prefix) == 0)
        {
            auto levels_string = arg.substr(FGEdlog_level_prefix.size());
            helpers::load_levels(levels_string);
        }
    }
}

inline void load_argv_levels(int argc, char **argv)
{
    load_argv_levels(argc, const_cast<const char **>(argv));
}

} // nameFGEace cfg
} // nameFGEace FGEdlog
