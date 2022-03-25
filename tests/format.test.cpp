#include <lib/test.hpp>
#include <lib/format.hpp>

#include <array>
#include <vector>
#include <string_view>
#include <map>

int main()
{
  "format"_suite(
      "<char*> should be equals to \"hello world!\""_test(
          []()
          {
            lib::test::assert::equals(
                "# #!"_fmt("hello", "world"),
                "hello world!");
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
      "<std::vector> should be equals to {1, 2, 3}"_test(
          []
          {
            std::vector<int> ints = {1, 2, 3};
            lib::test::assert::equals("#"_fmt(ints), "{1, 2, 3}");
          }),
      "<std::array> should be equals to {1, 2, 3}"_test(
          []
          {
            std::array<int, 3> ints = {1, 2, 3};
            lib::test::assert::equals("#"_fmt(ints), "{1, 2, 3}");
          }),
      "<std::array:std::array> should be equals to {{1}, {2}, {3}}"_test(
          []
          {
            std::array<std::array<int, 1>, 3> ints;
            ints[0] = {1};
            ints[1] = {2};
            ints[2] = {3};
            lib::test::assert::equals("#"_fmt(ints), "{{1}, {2}, {3}}");
          }),
      "<std::map> should be equals to {{1,1},{2,2},{3,3}}"_test(
          []
          {
            std::map<int, int> ints = {{1, 1}, {2, 2}, {3, 3}};
            lib::test::assert::equals("#"_fmt(ints), "{{1,1},{2,2},{3,3}}");
          }),
      "<std::map:int:std::map> should be equals to"
      "{{1,{{1,1}}},{2,{{2,2}}},{3,{{3,3}}}}"_test(
          []
          {
            std::map<int, std::map<int, int>> ints =
                {{1, {{1, 1}}},
                 {2, {{2, 2}}},
                 {3, {{3, 3}}}};
            lib::test::assert::equals(
                "#"_fmt(ints),
                "{{1,{{1,1}}},{2,{{2,2}}},{3,{{3,3}}}}");
          }))
      .run()
      .print();

  return 0;
}