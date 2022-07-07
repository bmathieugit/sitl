#ifndef __silt_test_hpp__
#define __silt_test_hpp__

#include <lib/basic_types.hpp>
#include <lib/vector.hpp>
#include <lib/string.hpp>
#include <lib/logger.hpp>
#include <lib/array.hpp>

#include <exception>

#include <typeinfo>

namespace sitl::test
{
  struct AssertError
  {
    String r;

    String reason() const noexcept
    {
      return r;
    }
  };

  struct Result
  {
    StringCRange descr;
    bool success;
    String reason;
  };

  template <Size n>
  struct Results
  {
    StringCRange descr;
    Array<Result, n> res;

    void print() const noexcept
    {
      logger::info("|- Test suite '", descr, '\'');

      for (const Result &r : res)
      {
        logger::info("  |- ", r.descr, " : ", r.success);

        if (not r.success)
          logger::info("    |- /!\\ ", r.reason);
      }

      Size ntotal = res.size();
      Size nsucceed = res.range().count_if(
          [](const Result &r)
          { return r.success; });

      logger::info("  |->>> tests ", nsucceed, '/', ntotal, " succeed");
    }
  };

  struct Test
  {
    StringCRange descr;
    void (*fn)();

    Result run() const noexcept
    try
    {
      fn();
      return {descr, true};
    }
    catch (const AssertError &e)
    {
      return {descr, false, e.reason()};
    }
    catch (const std::exception &e)
    {
      return {descr, false, e.what()};
    }
    catch (...)
    {
      return {descr, false, "unknown error"};
    }
  };

  template <Size n>
  struct TestSuite
  {
    StringCRange descr;
    Array<Test, n> tests;

    Results<n> run() const noexcept
    {
      Results<n> res;
      res.descr = descr;

      for (Size i = 0; i < tests.size(); ++i)
        res.res[i] = tests[i].run();

      return res;
    }
  };

  struct TestDefinition
  {
    StringCRange descr;

    Test operator()(void (*fn)())
    {
      return {descr, fn};
    }
  };

  struct TestSuiteDefinition
  {
    StringCRange descr;

    auto operator()(const auto... tests) -> TestSuite<sizeof...(tests)>
    {
      return {descr, Array<Test, sizeof...(tests)>{tests...}};
    }
  };
}

sitl::test::TestDefinition operator""_test(const char *descr, long unsigned int n)
{
  return {{descr, descr + n}};
}

sitl::test::TestSuiteDefinition operator""_suite(const char *descr, long unsigned int n)
{
  return {{descr, descr + n}};
}

namespace sitl::test::is
{
  struct Equals
  {
    template <typename A, typename E>
    void operator()(const A &actual,
                    const E &expected) const
    {
      if (!(actual == expected))
        throw AssertError(
            StringWriter().write(
                "(actual: ", actual,
                ") != (expected: ",
                expected, ')'));
    }
  };

  struct NotEquals
  {
    template <typename A, typename E>
    void operator()(const A &actual,
                    const E &expected) const
    {
      ;
      if (!(actual != expected))
        throw AssertError(
            StringWriter().write(
                "(actual: ", actual,
                ") == (expected: ",
                expected, ')'));
    }
  };

  template <typename Ex>
  struct Throws
  {
    template <typename F>
    void operator()(F &&f)
    try
    {
      f();
      throw AssertError(
          StringWriter().write(
              "expected thrown exception : ",
              typeid(Ex).name()));
    }
    catch (const Ex &e)
    {
      // nothing
    }
    catch (const std::exception &e)
    {
      throw AssertError(
          StringWriter().write(
              "expected thrown exception : ",
              typeid(Ex).name(),
              ", but actual : ", e.what()));
    }
    catch (...)
    {
      throw AssertError(
          StringWriter().write(
              "expected thrown exception : ",
              typeid(Ex).name(),
              ", but actual : (...)"));
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
    that(is::Equals(), a, b);
  }

  void not_equals(const auto &a, const auto &b)
  {
    that(is::NotEquals(), a, b);
  }

  template <typename Ex>
  void throws(auto &&f)
  {
    that(is::Throws<Ex>(), f);
  }
}

#endif