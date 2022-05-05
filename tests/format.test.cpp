#include <lib/format.hpp>
#include <lib/basic_types.hpp>
#include "tests.cpp"
#include <cstdio>

int main()
{
  TestResult result;

  test("#"_fmt(12).size() == 2, result);
  test("# #!"_fmt("hello", "world").size() == 12, result);
  test("#"_fmt(-12).size() == 3, result);
  test("#"_fmt('a').size() == 1, result);
  
  test("#"_fmt(12) == "12"_sv, result);
  test("# #!"_fmt("hello", "world") == "hello world!"_sv, result);
  test("#"_fmt(-12) == "-12"_sv, result);
  test("#"_fmt('a') == "a"_sv, result);

  print_result(result);

  return 0;
}