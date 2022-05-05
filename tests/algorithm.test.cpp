#include <lib/algorithm.hpp>
#include "tests.cpp"

int main()
{
  TestResult result;

  int i[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int *b = i;
  int *e = i + 10;

  int i2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int *b2 = i2;
  int *e2 = i2 + 10;

  int j[] = {0, 1, 2, 3, 4, 5, 5, 7, 8, 9};
  int *bj = j;
  int *ej = j + 10;

  int prefix[] = {0, 1, 2, 3};
  int *bp = prefix;
  int *ep = prefix + 4;

  test(*lib::FindAlgorithm()(b, e, 2) == 2, result);
  test(lib::FindAlgorithm()(b, e, 2) == i + 2, result);
  test(lib::FindAlgorithm()(b, e, 15) == e, result);
  test(lib::AfterAlgorithm()(b, e, 15) == e, result);
  test(lib::AfterAlgorithm()(b, e, 2) == i + 3, result);
  test(lib::CountAlgorithm()(b, e, 2) == 1, result);
  test(lib::CountAlgorithm()(b, e, 15) == 0, result);
  test(lib::EqualsAlgorithm()(b, e, b2, e2), result);
  test(!lib::EqualsAlgorithm()(b, e, bj, ej), result);
  test(lib::StartsWithAlgorithm()(b, e, bp, ep), result);
  test(!lib::StartsWithAlgorithm()(bp, ep, b, e), result);
  test(lib::AllOfAlgorithm()(b, e, lib::op::Greater(-1)), result);
  test(lib::AnyOfAlgorithm()(b, e, lib::op::GreaterEquals(0)), result);
  test(lib::NoneOfAlgorithm()(b, e, lib::op::Equals(-1)), result);

  print_result(result);
}