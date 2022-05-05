#include <lib/array.hpp>
#include "tests.cpp"

int main()
{
  TestResult result;

  lib::Array<int, 10> ints = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  test(ints.size() == 10, result);

  test(*ints.begin() == 0, result);
  test(ints.begin() == ints.data(), result);
  test(ints.begin() != ints.end(), result);
  test(ints.empty() == false, result);
  test(ints[0] == 0, result);
  test(ints[1] == 1, result);
  test(ints[2] == 2, result);
  test(ints[3] == 3, result);
  test(ints[4] == 4, result);
  test(ints[5] == 5, result);
  test(ints[6] == 6, result);
  test(ints[7] == 7, result);
  test(ints[8] == 8, result);
  test(ints[9] == 9, result);

  test(lib::rangeof(ints).starts_with(ints), result);
  test(lib::rangeof(ints).count() == ints.size(), result);
  test(lib::rangeof(ints).count_if([](const int &i)
                                   { return i % 2 == 0; }) == 5,
       result);
  test(lib::rangeof(ints).find(0) == ints.begin(), result);
  test(lib::rangeof(ints).find(25) == ints.end(), result);
  test(*lib::rangeof(ints).find_if([](const int &i)
                                   { return i == 6; }) == 6,
       result);
  test(lib::rangeof(ints).after(-1).count() == 0, result);

  test(lib::rangeof(ints).all_of([](const int &i)
                                 { return i < 100; }),
       result);

  test(lib::rangeof(ints).none_of([](const int &i)
                                  { return i < 0; }),
       result);
  test(lib::rangeof(ints).any_of([](const int &i)
                                 { return i == 1; }),
       result);
  print_result(result);

  return 0;
}