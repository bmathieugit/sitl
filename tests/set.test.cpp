#include <lib/set.hpp>
#include "tests.cpp"

int main()
{
  TestResult result;

  lib::Set<int> s = lib::Set<int>::from(1, 2, 3, 4, 5);

  test(s.size() == 5, result);
  test(!s.empty(), result);

  s.push(5);

  test(s.size() == 5, result);
  test(!s.empty(), result);

  s.push(6);

  test(s.size() == 6, result);
  test(!s.empty(), result);

  test(lib::Set<int>::from(1, 2, 3, 4, 5) == lib::Set<int>::from(1, 2, 3, 4, 5), result);

  print_result(result);
}