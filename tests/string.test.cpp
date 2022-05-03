#include <lib/string.hpp>
#include <lib/test.hpp>

int main()
{

  "String test suite"_suite(
      "test string build"_test(
          []
          {
            lib::String str("cou");
            lib::test::assert::equals(str.size(), lib::Size(3));
          }),
      "test string build and compare to 'cou'"_test(
          []
          {
            lib::String str("cou");
            lib::String str2("cou");
            lib::test::assert::equals(str, str2);
          }),
      "test string build"_test(
          []
          {
            lib::String str("cou");
            lib::test::assert::equals(str.size(), lib::Size(3));
          }))
      .run()
      .print();
}