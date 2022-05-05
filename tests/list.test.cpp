#include <lib/list.hpp>
#include "tests.cpp"

int main()
{
  TestResult result;

  lib::List<int> l;
  
  test(l.size() == 0, result);
  
  lib::List<int> l2 = lib::List<int>::from(1, 2, 3, 4);
  
  test(l2.size() == 4, result);
  test(*l2.begin() == 1, result);
  
  l2.insert(l2.begin(), 0);

  test(l2.size() == 5, result);
  test(*l2.begin() == 0, result);
  

  print_result(result);
}
