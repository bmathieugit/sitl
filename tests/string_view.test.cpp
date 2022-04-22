#include <lib/string_view.hpp>

#include <cstdio>

int main()
{
  int testok = 0;
  const int totaltest = 13;

  lib::StringView hello = "hello";

  testok += hello.size() == 5 ? 1 : 0;
  testok += *hello.begin() == 'h' ? 1 : 0;
  testok += *(hello.end() - 1) == 'o' ? 1 : 0;
  testok += hello[0] == 'h' ? 1 : 0;
  testok += hello[4] == 'o' ? 1 : 0;

  testok += hello.after('h').size() == 4 ? 1 : 0;
  testok += hello.after('h').size() == 4 ? 1 : 0;
  testok += hello.before('h').size() == 0 ? 1 : 0;
  testok += hello == lib::svfrom("hello") ? 1 : 0;
  testok += hello.before('h') == lib::svfrom("") ? 1 : 0;

  testok += hello.after('h') == lib::svfrom("ello") ? 1 : 0;
  testok += hello.starts_with(lib::svfrom("hel")) ? 1 : 0;
  testok += !hello.starts_with(lib::svfrom("el")) ? 1 : 0;

  std::printf("test OK %d/%d\n", testok, totaltest);
}