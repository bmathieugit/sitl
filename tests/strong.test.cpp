#include <lib/strong.hpp>
#include <lib/utility.hpp>
#include "tests.cpp"

int main()
{
  TestResult result;

  lib::Strong<int> i1 = new int(10);

  test(static_cast<bool>(i1), result);
  test(*i1 == 10, result);

  i1 = lib::move(lib::Strong<int>());

  test(!static_cast<bool>(i1), result);

  lib::Strong<int[]> is = new int[10];

  for (int i = 0; i < 10; ++i)
    is[i] = i;

  test(is[0] == 0, result);
  test(is[1] == 1, result);
  test(is[2] == 2, result);
  test(is[3] == 3, result);
  test(is[4] == 4, result);
  test(is[5] == 5, result);
  test(is[6] == 6, result);
  test(is[7] == 7, result);
  test(is[8] == 8, result);
  test(is[9] == 9, result);

  is = nullptr;

  test(!static_cast<bool>(is), result);

  print_result(result);
}
