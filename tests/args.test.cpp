#include <lib/args.hpp>
#include <lib/logger.hpp>
#include <lib/string.hpp>

#include "tests.cpp"

int main()
{
  TestResult result;

  sitl::String arg1 = "file=toto.sitl";
  arg1.push('\0');
  sitl::String arg2 = "verbose";
  arg2.push('\0');
  sitl::String arg3 = "int=-1200";
  arg3.push('\0');
  sitl::String arg4 = "uint=1200";
  arg4.push('\0');

  char *argv[] = {arg1.data(), arg2.data(),
                  arg3.data(), arg4.data()};
  int argc = 4;

  sitl::CommandLine cmdl(argc, argv);

  test(cmdl.size() == 4, result);
  test(!cmdl.empty(), result);
  test(cmdl.contains(sitl::sr("file")), result);
  test(cmdl.value(sitl::sr("file")) == sitl::sr("toto.sitl"), result);
  test(cmdl.value(sitl::sr("verbose2")) == sitl::sr(""), result);
  test(cmdl.flag(sitl::sr("file")), result);
  test(cmdl.flag(sitl::sr("verbose")), result);
  test(!cmdl.flag(sitl::sr("verbose2")), result);
  test(cmdl.uinteger(sitl::sr("uint")) == 1200, result);
  test(cmdl.integer(sitl::sr("uint")) == 1200, result);
  test(cmdl.integer(sitl::sr("int")) == -1200, result);
  test(cmdl.uinteger(sitl::sr("int")) == 0, result);
  test(cmdl.uinteger(sitl::sr("verbose")) == 0, result);
  test(cmdl.integer(sitl::sr("verbose")) == 0, result);


  print_result(result);
}