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
  testok += hello == "hello"_sv ? 1 : 0;
  testok += hello.before('h') == ""_sv ? 1 : 0;

  testok += hello.after('h') == "ello"_sv ? 1 : 0;
  testok += hello.starts_with("hel"_sv) ? 1 : 0;
  testok += !hello.starts_with("el"_sv) ? 1 : 0;

  std::printf("test OK %d/%d\n", testok, totaltest);
}