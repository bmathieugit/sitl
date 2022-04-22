#include <lib/array_view.hpp>
#include <lib/utility.hpp>
#include <cstdio>

int main()
{
  int testok = 0;
  const int totaltest = 13;
  constexpr auto length = [](const auto *c)
  { return lib::CStringUtils::length(c); };
  using LENGTH = decltype(length);
  lib::ArrayView<char, LENGTH> hello("hello");
  lib::ArrayView<char, LENGTH> ello("ello");
  lib::ArrayView<char, LENGTH> hel("hel");
  lib::ArrayView<char, LENGTH> el("el");
  lib::ArrayView<char, LENGTH> empty;

  testok += hello.size() == 5 ? 1 : 0;
  testok += *hello.begin() == 'h' ? 1 : 0;
  testok += *(hello.end() - 1) == 'o' ? 1 : 0;
  testok += hello[0] == 'h' ? 1 : 0;
  testok += hello[4] == 'o' ? 1 : 0;

  testok += hello.after('h').size() == 4 ? 1 : 0;
  testok += hello.before('h').size() == 0 ? 1 : 0;
  testok += hello == hello ? 1 : 0;
  testok += hello.before('h') == empty ? 1 : 0;
  testok += hello.after('h') == ello ? 1 : 0;

  testok += hello.starts_with(hel) ? 1 : 0;
  testok += !hello.starts_with(el) ? 1 : 0;
  testok += empty.empty() ? 1 : 0;

  std::printf("test OK %d/%d\n", testok, totaltest);
}