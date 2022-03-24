#ifndef __silt_test_hpp__
#define __silt_test_hpp__

#include <vector>
#include <string>
#include <string_view>
#include <exception>

#include <lib/logger.hpp>

namespace lib::test
{
  struct result
  {
    std::string_view descr;
    bool success;
  };

  template <size_t n>
  struct results
  {
    std::array<result, n> res;

    void print() const
    {
      for (const result r : res)
        logger::info("# : #", r.descr, r.success);
    }
  };

  struct test
  {
    std::string_view descr;
    void (*fn)();

    result run() const
    try
    {
      fn();
      return {descr, true};
    }
    catch (const std::exception &e)
    {
      lib::logger::error(" # : test failed #  ", std::string_view(e.what()), descr);
      return {descr, false};
    }
  };

  template <size_t n>
  struct test_suite
  {
    std::string_view descr;
    std::array<test, n> tests;

    results<n> run() const
    {
      results<n> res;

      for (size_t i = 0; i < tests.size(); ++i)
        res.res[i] = tests[i].run();

      return res;
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
    { return "assertion failed"; }
  };
}

lib::test::test_definition operator""_test(const char *descr, size_t n)
{
  return {{descr, n}};
}

lib::test::test_suite_definition operator""_suite(const char *descr, size_t n)
{
  return {{descr, n}};
}

namespace lib::test::is
{
  struct equals
  {
    template <typename T, typename O>
    void operator()(const T &t, const O &o)
    {
      if (not(t == o))
        throw lib::test::asserterror();
    }
  };
}

namespace lib::test::assert
{
  void that(auto is, const auto &...args)
  {
    is(args...);
  }

  void equals(const auto &a, const auto &b)
  {
    that(lib::test::is::equals{}, a, b);
  }
}

#endif