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
    struct intpad2dig
    {
      int i;
    };

    using day = intpad2dig;
    using month = intpad2dig;
    using year = intpad2dig;
    using hour = intpad2dig;
    using minute = intpad2dig;
    using second = intpad2dig;

    template <typename C,
              typename... params_t>
    void logging(level l,
                 std::basic_string_view<C> msg,
                 const params_t &...pms)
    {
      std::time_t tnow = std::time(nullptr);
      std::tm *now = std::localtime(&tnow);

      ios::fprintf(stdout, "#/#/# #:#:# : ",
                   day{now->tm_mday},
                   month{now->tm_mon},
                   1900 + now->tm_year,
                   hour{now->tm_hour},
                   minute{now->tm_min},
                   second{now->tm_sec});

      ios::fprintf(stdout, "[#] : ", l);
      ios::fprintfln(stdout, msg, pms...);
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

  void trace(
      std::wstring_view msg,
      const auto &...pms)
  {
    impl::logging(level::trace, msg, pms...);
  }

  void debug(
      std::wstring_view msg,
      const auto &...pms)
  {
    impl::logging(level::debug, msg, pms...);
  }

  void info(
      std::wstring_view msg,
      const auto &...pms)
  {
    impl::logging(level::info, msg, pms...);
  }

  void warn(
      std::wstring_view msg,
      const auto &...pms)
  {
    impl::logging(level::warn, msg, pms...);
  }

  void error(
      std::wstring_view msg,
      const auto &...pms)
  {
    impl::logging(level::error, msg, pms...);
  }

  void fatal(
      std::wstring_view msg,
      const auto &...pms)
  {
    impl::logging(level::fatal, msg, pms...);
  }
}

namespace fmt
{
  template <>
  struct formatter<logger::impl::intpad2dig>
  {
    template <typename C>
    void operator()(
        std::basic_string<C> &buff,
        const logger::impl::intpad2dig &ipad2)
    {
      if (0 <= ipad2.i and ipad2.i <= 9)
        formatter<C>{}(buff, '0');

      formatter<int>{}(buff, ipad2.i);
    }
  };

  template <>
  struct formatter<logger::level>
  {
    template <typename C>
    void operator()(
        std::basic_string<C> &buff,
        logger::level l)
    {
      constexpr static std::basic_string_view<C> ltable[] = {
          "trace", "debug", "info", "warn", "error", "fatal"};
      formatter<std::basic_string_view<C>>{}(buff, ltable[(int)l]);
    }
  };
}

#endif