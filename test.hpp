#ifndef __clon_test_hpp__
#define __clon_test_hpp__

#include "format.hpp"
#include "ios.hpp"

#define test_equals(actual, expected)             \
  lib::fprintfln(stdout, "===== at l.# test # == # : #",   \
                __LINE__, (#actual), (#expected), \
                (((actual) == (expected)) ? "OK" : "KO"));

#define test_not_equals(actual, expected)         \
  lib::fprintfln(stdout, "===== at l.# test # != # : #",   \
                __LINE__, (#actual), (#expected), \
                (((actual) != (expected)) ? "OK" : "KO"));

#define test_catch(torun, exception)  \
  try                                 \
  {                                   \
    (torun);                          \
    lib::fprintln(stdout, "no exception KO");  \
  }                                   \
  catch (exception & e)               \
  {                                   \
    lib::fprintln(stdout, "OK");               \
  }                                   \
  catch (...)                         \
  {                                   \
    lib::fprintln(stdout, "bad exception KO"); \
  }

#define run_test(testname)                      \
  lib::fprintln(stdout, "\n--------------------------"); \
  lib::fprintfln(stdout, "=  test file #", __FILE__);    \
  lib::fprintfln(stdout, "=== run #", #testname);        \
  testname();

#endif
