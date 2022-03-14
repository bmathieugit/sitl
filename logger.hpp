#ifndef __log_logger_hpp__
#define __log_logger_hpp__

#include <cstdio>
#include <string_view>
#include <ctime>

#include "ios.hpp"
#include "format.hpp"

namespace logger
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

  namespace impl
  {
    struct pad2d
    {
      int i;
    };

    void logging(level l,
                 std::string_view msg,
                 const auto &...pms)
    {
      std::time_t tnow = std::time(nullptr);
      std::tm *now = std::localtime(&tnow);

      ios::fprintf(stdout, "#/#/# #:#:# : [#] : ",
                   pad2d{now->tm_mday}, pad2d{now->tm_mon},
                   1900 + now->tm_year, pad2d{now->tm_hour},
                   pad2d{now->tm_min}, pad2d{now->tm_sec}, l);
      ios::fprintln(stdout, fmt::format(msg, pms...));
    }
  }

  void trace(
      std::string_view msg,
      const auto &...pms)
  {
    impl::logging(level::trace, msg, pms...);
  }

  void debug(
      std::string_view msg,
      const auto &...pms)
  {
    impl::logging(level::debug, msg, pms...);
  }

  void info(
      std::string_view msg,
      const auto &...pms)
  {
    impl::logging(level::info, msg, pms...);
  }

  void warn(
      std::string_view msg,
      const auto &...pms)
  {
    impl::logging(level::warn, msg, pms...);
  }

  void error(
      std::string_view msg,
      const auto &...pms)
  {
    impl::logging(level::error, msg, pms...);
  }

  void fatal(
      std::string_view msg,
      const auto &...pms)
  {
    impl::logging(level::fatal, msg, pms...);
  }
}

namespace fmt
{
  template <>
  struct formatter<logger::impl::pad2d>
      : formatter<int>
  {
    void format(
        std::string &buff,
        logger::impl::pad2d p2)
    {
      if (0 <= p2.i and p2.i <= 9)
        formatter<char>::format(buff, '0');

      formatter<int>::format(buff, p2.i);
    }
  };

  template <>
  struct formatter<logger::level>
      : formatter<std::string_view>
  {
    void format(
        std::string &buff,
        logger::level l)
    {
      constexpr std::string_view ltable[] = {
          "trace", "debug", "info", "warn", "error", "fatal"};
      formatter<std::string_view>::format(buff, ltable[(int)l]);
    }
  };
}

#endif
