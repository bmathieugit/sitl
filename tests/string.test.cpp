#include <lib/string.hpp>
#include "tests.cpp"
#include <cstdio>

int main()
{
  TestResult result;
  sitl::String str("cou");
  sitl::String str2("cou");

  test(str.size() == 3, result);
  test(str == str2, result);

  str.push_front('c');

  test(str.size() == 4, result);
  test(str[0] == 'c', result);
  test(str[1] == 'c', result);
  test(str[2] == 'o', result);
  test(str[3] == 'u', result);
  test(str.begin() != str.end(), result);
  test(str.begin() == str.data(), result);
  test(!str.empty(), result);

  str2.clear();

  test(str2.size() == 0, result);
  test(str2.empty(), result);

  str2.push_back('c');

  test(str2.size() == 1, result);
  test(!str2.empty(), result);
  
  str2.append(sitl::sr("ou")); 
  
  test(str2.size() == 3, result);

  str2.append(sitl::sr("c"));

  test(str2.size() == 4, result);

  print_result(result);

  return 0;
}
