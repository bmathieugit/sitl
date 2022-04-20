#include <lib/list.hpp>
#include <lib/test.hpp>

int main()
{
  "Test suite 'list'"_suite(
      "test build a default list"_test(
          []
          {
            lib::List<int> l;
            lib::test::assert::equals(l.size(), 0);
          }),
      "test build a list with initilizer_list"_test(
          []
          {
            lib::List<int> l = {0, 1, 2, 3};
            lib::test::assert::equals(l.size(), 4);
            lib::test::assert::equals(*l.begin(), 0);
          }),
      "test build a list and insert an item at begin"_test(
          []
          {
            lib::List<int> l = {0, 1, 2, 3};
            lib::test::assert::equals(l.size(), 4);
            lib::test::assert::equals(*l.begin(), 0);

            l.insert(l.begin(), 1);
            lib::test::assert::equals(l.size(), 5);
            lib::test::assert::equals(*l.begin(), 1);
          }),
      "test build a list and insert an item at end"_test(
          []
          {
            lib::List<int> l = {0, 1, 2, 3};
            lib::test::assert::equals(l.size(), 4);
            lib::test::assert::equals(*l.begin(), 0);

            l.insert(l.end(), 1);
            lib::test::assert::equals(l.size(), 5);
            auto it = l.begin();
            it++;
            it++;
            it++;
            it++;
            lib::test::assert::equals(*it, 1);
          }),
      "test build a list and insert an item at inner"_test(
          []
          {
            lib::List<int> l = {0, 1, 2, 3};
            lib::test::assert::equals(l.size(), 4);
            lib::test::assert::equals(*l.begin(), 0);
            auto it = l.begin();
            it++;
            it++;
            l.insert(it, 1);
            auto it2 = l.begin();
            it2++;
            it2++;
            lib::test::assert::equals(l.size(), 5);
            lib::test::assert::equals(*it2, 1);
          }),
      "test equality between two same lists"_test(
          []
          {
            lib::List<int> i = {0, 2, 3, 4, 5, 6, 7, 8, 9};
            lib::List<int> i2 = {0, 2, 3, 4, 5, 6, 7, 8, 9};
            lib::test::assert::equals(i, i);
            lib::test::assert::equals(i, i2);
          }),
      "test not equality between two different lists"_test(
          []
          {
            lib::List<int> i = {0, 2, 3, 4, 5, 6, 7, 8, 9};
            lib::List<int> i2 = {0, 2, 3, 4, 5, 6, 7, 8};
            lib::test::assert::not_equals(i, i2);
          }))
      .run()
      .print();
}