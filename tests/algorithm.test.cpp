#include <lib/algorithm.hpp>

#include <cstdio>

int main()
{
  int testok = 0;
  const int totaltest = 14;

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

  testok += *lib::FindAlgorithm()(b, e, 2) == 2 ? 1 : 0;
  testok += lib::FindAlgorithm()(b, e, 2) == i + 2 ? 1 : 0;
  testok += lib::FindAlgorithm()(b, e, 15) == e ? 1 : 0;
  testok += lib::AfterAlgorithm()(b, e, 15) == e ? 1 : 0;
  testok += lib::AfterAlgorithm()(b, e, 2) == i + 3 ? 1 : 0;
  testok += lib::CountAlgorithm()(b, e, 2) == 1 ? 1 : 0;
  testok += lib::CountAlgorithm()(b, e, 15) == 0 ? 1 : 0;
  testok += lib::EqualsAlgorithm()(b, e, b2, e2) ? 1 : 0;
  testok += !lib::EqualsAlgorithm()(b, e, bj, ej) ? 1 : 0;
  testok += lib::StartsWithAlgorithm()(b, e, bp, ep) ? 1 : 0;
  testok += !lib::StartsWithAlgorithm()(bp, ep, b, e) ? 1 : 0;
  testok += lib::AllOfAlgorithm()(b, e, lib::op::Greater(-1)) ? 1 : 0;
  testok += lib::AnyOfAlgorithm()(b, e, lib::op::GreaterEquals(0)) ? 1 : 0;
  testok += lib::NoneOfAlgorithm()(b, e, lib::op::Equals(-1)) ? 1 : 0;

  std::printf("test OK %d/%d\n", testok, totaltest);
}