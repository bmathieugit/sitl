#include <lib/map.hpp>
#include <lib/test.hpp>

int main()
{
  "Map test-suite"_suite(
    "should init empty map"_test([]{
      sitl::Map<int, int> ii; 
      sitl::test::assert::equals(ii.size(), 0);
    }), 
    "should add new entry in map"_test([]{
      sitl::Map<int, int> ii; 

      ii.push(1, 10);
      ii.push(2, 20);
      sitl::test::assert::equals(ii.size(), 2);
      sitl::test::assert::equals(ii.at(1).get(), 10);
      sitl::test::assert::equals(ii.at(2).get(), 20);
      ii.push(1, 12);
      sitl::test::assert::equals(ii.size(), 2);
      sitl::test::assert::equals(ii.at(1).get(), 12);
      
})
  ).run().print();
}
