#include <lib/test.hpp>
#include <lib/format.hpp>
#include <lib/vector.hpp>

int main()
{
  "format"_suite(
      "<char*> should be equals to \"hello world!\""_test(
          []()
          {
            lib::test::assert::equals("# #!"_fmt("hello", "world"), "hello world!");
          }),
      "<int-0> should be equals to 0"_test(
          []
          {
            lib::test::assert::equals("#"_fmt(0), "0");
          }),
      "<int-12> should be equals to 12"_test(
          []
          {
            lib::test::assert::equals("#"_fmt(12), "12");
          }),
      "<char-'a'> should be equals to 'a'"_test(
          []
          {
            lib::test::assert::equals("#"_fmt('a'), "a");
          }),
      "<Vector> should be equals to {1, 2, 3}"_test(
          []
          {
            lib::Vector<int> ints = {1, 2, 3};
            lib::test::assert::equals("#"_fmt(ints), "{1, 2, 3}");
          }))
      .run()
      .print();

  return 0;
}