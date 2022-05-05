#include <lib/vector.hpp>
#include "tests.cpp"

int main()
{
  TestResult result;

  lib::Vector<int> ints;

  test(ints.size() == 0, result);
  test(ints.empty(), result);

  lib::Vector<int> ints2 = lib::Vector<int>::from(1, 2, 3, 4, 5, 6, 7, 8, 9);

  test(ints2.size() == 9, result);
  test(!ints2.empty(), result);
  test(ints2 == ints2, result);
  test(ints2 == lib::Vector<int>::from(1, 2, 3, 4, 5, 6, 7, 8, 9), result);
  test(ints2[0] = 1, result);
  test(ints2[1] = 2, result);
  test(ints2[2] = 3, result);
  test(ints2[3] = 4, result);
  test(ints2[4] = 5, result);
  test(ints2[5] = 6, result);
  test(ints2[6] = 7, result);
  test(ints2[7] = 8, result);
  test(ints2[8] = 9, result);

  ints2.push_back(10);

  test(ints2.size() == 10, result);
  test(ints2[9] = 10, result);

  ints2.push_front(-1);

  test(ints2[0] == -1, result);
  test(ints2.size() == 11, result);
  test(ints2[10] = 10, result);

  print_result(result);
}