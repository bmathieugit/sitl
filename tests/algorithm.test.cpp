#include <lib/range.hpp>
#include "tests.cpp"

int main()
{
  TestResult result;

  int  tmp[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto i = lib::rangeof(tmp);

  int tmp2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto i2 = lib::rangeof(tmp2);

  int tmp3[] = {0, 1, 2, 3, 4, 5, 5, 7, 8, 9};
  auto i3 = lib::rangeof(tmp3);

  int tmp4[] = {0, 1, 2, 3};
  auto i4 = lib::rangeof(tmp4);

  test(*i.find(2) == 2, result);
  test(i.find(2) == tmp + 2, result);
  test(i.find(15) == i.end(), result);
  test(i.after(15).begin() == i.end(), result);
  test(i.after(2).begin() == tmp + 3, result);
  test(i.count(2) == 1, result);
  test(i.count(15) == 0, result);
  test(i == i2, result);
  test(!(i== i3), result);
  test(i.starts_with(i4), result);
  test(!i4.starts_with(i), result);
  test(i.all_of(lib::op::Greater(-1)), result);
  test(i.any_of(lib::op::GreaterEquals(0)), result);
  test(i.none_of(lib::op::Equals(-1)), result);

  print_result(result);
}