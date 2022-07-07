#include <lib/test.hpp>
#include <lib/tuple.hpp>
#include <lib/string.hpp>

int main()
{
  "Tuple test suite"_suite(
      "should build basic tuple of int and char"_test(
          []
          {
            sitl::Tuple<int, char> t(12, 'a');
            sitl::test::assert::equals(12, sitl::get<0>(t));
            sitl::test::assert::equals('a', sitl::get<1>(t));
          }),
      "should copy tuple int and char"_test(
          []
          {
            sitl::Tuple<int, char> t(12, 'a');
            sitl::Tuple<int, char> t2 = t;
            sitl::test::assert::equals(sitl::get<0>(t), sitl::get<0>(t2));
            sitl::test::assert::equals(sitl::get<1>(t), sitl::get<1>(t2));
          }),

      "should move tuple string and int"_test(
          []
          {
            sitl::Tuple<sitl::String, int> t("toto", 12);
            sitl::Tuple<sitl::String, int> t2 = move(t);
            sitl::test::assert::equals(sitl::String(""), sitl::get<0>(t));
            sitl::test::assert::equals(sitl::String("toto"), sitl::get<0>(t2));
            sitl::test::assert::equals(12, sitl::get<1>(t2));
          }))
      .run()
      .print();
}