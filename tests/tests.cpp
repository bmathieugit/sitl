#ifndef __test_tests_tpp__
#define __test_tests_tpp__

#include <lib/basic_types.hpp>
#include <lib/iostream.hpp>

struct TestResult
{
  lib::Size nbsucceed = 0;
  lib::Size nbtotal = 0;
};

constexpr void test(bool expression, TestResult &result)
{
  if (expression)
    ++result.nbsucceed;
  ++result.nbtotal;
}

inline void print_result(const TestResult &result)
{
  lib::println("test OK ", result.nbsucceed, '/', result.nbtotal);
}

#endif