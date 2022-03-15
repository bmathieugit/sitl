#ifndef __log_logger_hpp__
#define __log_logger_hpp__

#include <cstdio>
#include <string_view>
#include <ctime>

#include "ios.hpp"
#include "format.hpp"

namespace sitl::logger
{
  enum class level : int
  {
    trace = 0,
    debug = 1,
    info = 2,
    warn = 3,
    error = 4,
    fatal = 5
  };

  struct pad2d
  {
    int i;
  };

  void log(level l,
           std::string_view msg,
           const auto &...pms);

  void trace(std::string_view msg,
             const auto &...pms);

  void debug(std::string_view msg,
             const auto &...pms);

  void info(std::string_view msg,
            const auto &...pms);

  void warn(std::string_view msg,
            const auto &...pms);

  void error(std::string_view msg,
             const auto &...pms);

  void fatal(std::string_view msg,
             const auto &...pms);
}

template <>
struct sitl::fmt::formatter<sitl::logger::pad2d>
{
  void format(
      std::string &buff,
      sitl::logger::pad2d p2)
  {
    if (0 <= p2.i and p2.i <= 9)
      sitl::fmt::formatter<char>{}.format(buff, '0');

    sitl::fmt::formatter<int>{}.format(buff, p2.i);
  }
};

template <>
struct sitl::fmt::formatter<sitl::logger::level>
{
  void format(
      std::string &buff,
      sitl::logger::level l)
  {
    constexpr std::string_view ltable[] = {
        "trace", "debug", "info", "warn", "error", "fatal"};
    sitl::fmt::formatter<std::string_view>{}.format(buff, ltable[(int)l]);
  }
};

void sitl::logger::log(sitl::logger::level l,
                       std::string_view msg,
                       const auto &...pms)
{
  std::time_t tnow = std::time(nullptr);
  std::tm *now = std::localtime(&tnow);

  sitl::ios::fprintf(stdout, "#/#/# #:#:# : [#] : ",
                     sitl::logger::pad2d{now->tm_mday},
                     sitl::logger::pad2d{now->tm_mon},
                     1900 + now->tm_year,
                     sitl::logger::pad2d{now->tm_hour},
                     sitl::logger::pad2d{now->tm_min},
                     sitl::logger::pad2d{now->tm_sec}, l);
  sitl::ios::fprintfln(stdout, msg, pms...);
}

void sitl::logger::trace(std::string_view msg,
                         const auto &...pms)
{
  sitl::logger::log(level::trace, msg, pms...);
}

void sitl::logger::debug(std::string_view msg,
                         const auto &...pms)
{
  sitl::logger::log(level::debug, msg, pms...);
}

void sitl::logger::info(std::string_view msg,
                        const auto &...pms)
{
  sitl::logger::log(level::info, msg, pms...);
}

void sitl::logger::warn(std::string_view msg,
                        const auto &...pms)
{
  sitl::logger::log(level::warn, msg, pms...);
}

void sitl::logger::error(std::string_view msg,
                         const auto &...pms)
{
  sitl::logger::log(level::error, msg, pms...);
}

void sitl::logger::fatal(std::string_view msg,
                         const auto &...pms)
{
  sitl::logger::log(level::fatal, msg, pms...);
}

#endif
