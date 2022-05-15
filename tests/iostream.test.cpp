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

  test(sw.write(-12) == sv("-12") , result);
  test(sw.write(12) == sv("12") , result);
  test(sw.write(true) == sv("true") , result);
  test(sw.write(false) == sv("false") , result);
  test(sw.write("coucou") == sv("coucou") , result);
  test(sw.write(' ') == sv(" ") , result);
  test(sw.write("hello", ' ', "world !") == sv("hello world !") , result);

  print_result(result);

  return 0;
}
