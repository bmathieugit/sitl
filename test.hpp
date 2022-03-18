#ifndef __silt_test_hpp__
#define __silt_test_hpp__

#include <vector>
#include <string>
#include <string_view>
#include <exception>

#include "logger.hpp"

namespace sitl::test
{
  struct result
  {
  };

  struct test
  {
    std::string_view descr;
    void (*fn)();

    result run() const
    try
    {
      logger::info("test");
      fn();
      return {};
    }
    catch (const std::exception &e)
    {
      sitl::logger::error(" # : test failed #  ", std::string_view(e.what()), descr);
      return {};
    }
  };

  template <size_t n>
  struct test_suite
  {
    std::string_view descr;
    std::array<test, n> tests;
    std::array<result, n> results;

    void run() const
    {
      for (const test &t : tests)
        t.run();
    }
  };

  struct test_definition
  {
    std::string_view descr;

    test operator()(void (*fn)())
    {
      return {descr, fn};
    }
  };

  struct test_suite_definition
  {
    std::string_view descr;

    auto operator()(const auto... tests)
        -> test_suite<sizeof...(tests)>
    {
      return {descr, {tests...}};
    }
  };

  struct asserterror : std::exception
  {
    virtual const char *
    what() const noexcept
    {
      return "assertion failed";
    }
  };

}

sitl::test::test_definition operator""_test(const char *descr, size_t n)
{
  return {{descr, n}};
}

sitl::test::test_suite_definition operator""_suite(const char *descr, size_t n)
{
  return {{descr, n}};
}

namespace sitl::test::is
{
  struct equals
  {
    template <typename T, typename O>
    void operator()(const T &t, const O &o)
    {
      sitl::logger::info("coucou # == #", t, o);
      if (not(t == o))
      {
        logger::error("yoooo");
        throw sitl::test::asserterror();
      }
    }
  };
}

namespace sitl::test::assert
{
  void that(auto is, const auto &...args)
  {
    is(args...);
  }

  void equals(const auto &a, const auto &b)
  {
    that(sitl::test::is::equals{}, a, b);
  }
}

#endif