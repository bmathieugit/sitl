#include "format.hpp"
#include "test.hpp"

int main()
{
  test_equals(lib::format("this is #", "42"), "this is 42");
  test_equals(lib::format("this is #", 42), "this is 42");
  test_equals(lib::format("this is #", true), "this is true");
}
