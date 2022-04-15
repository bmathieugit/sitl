#include <lib/array_view.hpp>

#include <cstdio>

int main()
{
  int testok = 0;
  const int totaltest = 13;

  lib::ArrayView<char> hello("hello", 5);
  lib::ArrayView<char> ello("ello", 4);
  lib::ArrayView<char> hel("hel", 3);
  lib::ArrayView<char> el("el", 2);
  lib::ArrayView<char> empty;

  testok += hello.size() == 5 ? 1 : 0;
  testok += *hello.begin() == 'h' ? 1 : 0;
  testok += *(hello.end() - 1) == 'o' ? 1 : 0;
  testok += hello[0] == 'h' ? 1 : 0;
  testok += hello[4] == 'o' ? 1 : 0;
  testok += hello.after('h').size() == 4 ? 1 : 0;

  testok += hello.after('h').size() == 4 ? 1 : 0;
  testok += hello.before('h').size() == 0 ? 1 : 0;
  testok += hello == hello ? 1 : 0;
  testok += hello.before('h') == empty ? 1 : 0;
  testok += hello.after('h') == ello ? 1 : 0;
  testok += hello.starts_with(hel) ? 1 : 0;
  testok += !hello.starts_with(el) ? 1 : 0;

  std::printf("test OK %d/%d\n", testok, totaltest);
}