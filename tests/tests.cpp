#ifndef __test_tests_tpp__
#define __test_tests_tpp__

#include <lib/basic_types.hpp>
#include <lib/iostream.hpp>

struct TestResult
{
  sitl::Size nbsucceed = 0;
  sitl::Size nbtotal = 0;
};

constexpr void test(bool expression, TestResult &result)
{
  if (expression)
    ++result.nbsucceed;
  ++result.nbtotal;
}

inline void print_result(const TestResult &result)
{
  sitl::println("test OK ", result.nbsucceed, '/', result.nbtotal);
}

#endif