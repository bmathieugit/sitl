#include <lib/range.hpp>
#include "tests.cpp"

int main()
{
  TestResult result;

  constexpr auto i = sitl::range((const int[]){0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  constexpr auto i2 = i;
  constexpr auto i3 = sitl::range((const int[]){0, 1, 2, 3, 4, 5, 5, 7, 8, 9});
  constexpr auto i4 = sitl::range((const int[]){0, 1, 2, 3});

  test(*i.find(2) == 2, result);
  test(i.find(2) == i.begin() + 2, result);
  test(i.find(15) == i.end(), result);
  test(i.after(15).begin() == i.end(), result);
  test(i.after(2).begin() == i.begin() + 3, result);
  test(i.count(2) == 1, result);
  test(i.count(15) == 0, result);
  test(i == i2, result);
  test(!(i == i3), result);
  test(i.starts_with(i4), result);
  test(!i4.starts_with(i), result);
  test(i.all_of(op::Greater(-1)), result);
  test(i.any_of(op::GreaterEquals(0)), result);
  test(i.none_of(op::Equals(-1)), result);

  print_result(result);
}
