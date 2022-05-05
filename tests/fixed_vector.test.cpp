#include <lib/fixed_vector.hpp>
#include "tests.cpp"
#include <cstdio>

int main()
{
  TestResult result;

  lib::FixedVector<int> ints(12);

  for (lib::Size i = 0; i < 12; ++i)
    ints.push_back(i);

  test(ints.size() == 12, result);
  test(ints.capacity() == 12, result);
  
  lib::FixedVector<int> ints2(lib::FixedVector<int>::from(1, 2, 3));

  test(ints2.size() == 3, result);
  test(ints2.capacity() == 3, result);

  ints2.push_back(4);

  test(ints2.size() == 3, result);
  test(ints2.capacity() == 3, result);

  test(ints2[0] == 1, result);
  test(ints2[1] == 2, result);
  test(ints2[2] == 3, result);

  ints2.clear(); 

  test(ints2.size() == 0, result);
  test(ints2.capacity() == 3, result);

  auto ints3 = lib::FixedVector<int>::from(1, 2, 3, 4, 5);
  auto ints4 = lib::FixedVector<int>::from(1, 2, 3, 4, 5);

  test(ints3 == ints4, result);
  print_result(result);
  
  return 0;
}