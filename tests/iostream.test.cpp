#include <lib/iostream.hpp>
#include <lib/basic_types.hpp>
#include "tests.cpp"
#include <cstdio>

int main()
{
  TestResult result;

  sitl::StringWriter sw;

  auto ss1 = sw.write(-12);
  auto ss2 = sw.write(12);
  auto ss3 = sw.write(true);
  auto ss4 = sw.write(false);
  auto ss5 = sw.write("coucou");
  auto ss6 = sw.write(' ');
  auto ss7 = sw.write("hello", ' ', "world !");

  test(ss1.size() == 3, result);
  test(ss2.size() == 2, result);
  test(ss3.size() == 4, result);
  test(ss4.size() == 5, result);
  test(ss5.size() == 6, result);
  test(ss6.size() == 1, result);
  test(ss7.size() == 13, result);

  constexpr auto s1 = sitl::sr("-12");
  constexpr auto s2 = sitl::sr("12");
  constexpr auto s3 = sitl::sr("true");
  constexpr auto s4 = sitl::sr("false");
  constexpr auto s5 = sitl::sr("coucou");
  constexpr auto s6 = sitl::sr(" ");
  constexpr auto s7 = sitl::sr("hello world !");

  test(ss1 == s1, result);
  test(ss2 == s2, result);
  test(ss3 == s3, result);
  test(ss4 == s4, result);
  test(ss5 == s5, result);
  test(ss6 == s6, result);
  test(ss7 == s7, result);

  print_result(result);

  return 0;
}
