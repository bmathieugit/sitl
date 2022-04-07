#include <lib/vector.hpp>
#include <lib/test.hpp>

#include <iostream>

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
            lib::Vector<int> ints({1, 2, 3});
            lib::test::assert::equals(ints.size(), lib::Size(3));
            lib::test::assert::equals(ints.capacity(), lib::Size(3));
          }),
      "test of vector build and push_back with 4"_test(
          []
          {
            lib::Vector<int> ints({1, 2, 3});
            lib::test::assert::equals(ints.size(), lib::Size(3));
            ints.push_back(4);
            lib::test::assert::equals(ints.size(), lib::Size(4));
          }),
      "test of vector build and remove an item"_test(
          []
          {
            lib::Vector<int> ints({1, 2, 3, 4, 5});
            ints.remove(2);
            lib::test::assert::equals(ints.size(), lib::Size(4));
          }),
      "test of vector build and random access"_test(
          []
          {
            lib::Vector<int> ints({1, 2, 3, 4, 5});
            lib::test::assert::equals(ints[0], 1);
            lib::test::assert::equals(ints[1], 2);
            lib::test::assert::equals(ints[2], 3);
            lib::test::assert::equals(ints[3], 4);
            lib::test::assert::equals(ints[4], 5);
          }),
      "test of vector build and pop_back"_test(
          []
          {
            lib::Vector<int> ints({1, 2, 3, 4, 5});
            ints.pop_back();
            lib::test::assert::equals(ints.size(), lib::Size(4));
          }),
      "test of vector build and pop_front"_test(
          []
          {
            lib::Vector<int> ints({1, 2, 3, 4, 5});
            ints.pop_back();
            lib::test::assert::equals(ints.size(), lib::Size(4));
          }),
      "test of vector build and clear"_test(
          []
          {
            lib::Vector<int> ints({1, 2, 3, 4, 5});
            ints.clear();
            lib::test::assert::equals(ints.size(), lib::Size(0));
          }))
      .run()
      .print();
}