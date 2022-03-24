#include <lib/test.hpp>
#include <lib/format.hpp>

int main()
{
  "format"_suite(
      "should be equals to \"hello world!\""_test(
          []()
          {
            lib::test::assert::equals(
                "# #!"_fmt("hello", "world"),
                "hello world!");
          }),
      "should be equals to 0"_test(
          []
          {
            lib::test::assert::equals("#"_fmt(0), "0");
          }),
      "should be equals to 12"_test(
          []
          {
            lib::test::assert::equals("#"_fmt(12), "12");
          }),
      "should be equals to 'a'"_test(
          []
          {
            lib::test::assert::equals("#"_fmt('a'), "a");
          }))
      .run()
      .print();

  return 0;
}