#include <lib/set.hpp>
#include <lib/test.hpp>

int main()
{
  "Test suite 'set'"_suite(
      "test a simple build of set"_test(
          []
          {
            lib::Set<int> i = lib::Set<int>::from(1, 2, 3, 4, 5);
            lib::test::assert::equals(i.size(), lib::Size(5));
          }), 
      "test a build set step by step"_test(
        []
        {
          lib::Set<int> ints=lib::Set<int>::from(1);
          ints.push(0); 
          ints.push(4); 
          ints.push(2); 
          ints.push(2); 
          ints.push(3);

          lib::test::assert::equals(ints.size(), lib::Size(5));
        }
      ))
      .run()
      .print();
}