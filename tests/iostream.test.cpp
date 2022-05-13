#include <lib/iostream.hpp>
#include <lib/basic_types.hpp>
#include "tests.cpp"
#include <cstdio>

int main()
{
  TestResult result;

  lib::StringWriter sw;
  test(sw.write(-12).size() == 3, result);
  test(sw.write(12).size() == 2, result);
  test(sw.write(true).size() == 4, result);
  test(sw.write(false).size() == 5, result);
  test(sw.write("coucou").size() == 6, result);
  test(sw.write(' ').size() == 1, result);
  test(sw.write("hello", ' ', "world !").size() == 13, result);

  test(sw.write(-12) == "-12"_sv, result);
  test(sw.write(12) == "12"_sv, result);
  test(sw.write(true) == "true"_sv, result);
  test(sw.write(false) == "false"_sv, result);
  test(sw.write("coucou") == "coucou"_sv, result);
  test(sw.write(' ') == " "_sv, result);
  test(sw.write("hello", ' ', "world !") == "hello world !"_sv, result);

  print_result(result);

  return 0;
}