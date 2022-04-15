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
      "test string build with buffer"_test(
          []
          {
            lib::Buffer<char> buff(10);
            buff.push_back('c');
            buff.push_back('o');
            buff.push_back('u');
            buff.push_back('c');
            buff.push_back('o');
            buff.push_back('u');
            lib::String cou(buff.flush());
            lib::test::assert::equals(cou.size(), lib::Size(6));
            lib::test::assert::equals(cou.capacity(), lib::Size(10));
            lib::test::assert::equals(cou, "coucou");
          }),
      "test string build and compare to 'cou'"_test(
          []
          {
            lib::String str("cou");
            lib::String str2("cou");
            lib::test::assert::equals(str, str2);
          }),
      "test string build and pop_back and compare to 'co'"_test(
          []
          {
            lib::String str("cou");
            str.pop_back();
            lib::test::assert::equals(str, "co");
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