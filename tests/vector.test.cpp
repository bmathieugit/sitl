#include <lib/vector.hpp>
#include <lib/test.hpp>

int main()
{
  "Test of vector"_suite(
      "test of vector default build"_test(
          []
          {
            lib::Vector<int> ints;

            lib::test::assert::equals(ints.size(), lib::Size(0));
            lib::test::assert::equals(ints.capacity(), lib::Size(0));
          }),
      "test of vector size"_test(
          []
          {
            lib::Vector<int> ints(12);

            for (lib::Size i = 0; i < 12; ++i)
              ints.push_back(i);

            lib::test::assert::equals(ints.size(), lib::Size(12));
            lib::test::assert::equals(ints.capacity(), lib::Size(12));
          }),
      "test of vector build by {1, 2, 3}"_test(
          [] 
          {
            lib::Vector<int> ints({1,2,3});
            lib::test::assert::equals(ints.size(), lib::Size(3));
            lib::test::assert::equals(ints.capacity(), lib::Size(3));
          }))
      .run()
      .print();
}