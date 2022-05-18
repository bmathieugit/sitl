#include <lib/args.hpp>
#include <lib/logger.hpp>
#include <lib/string.hpp>

#include "tests.cpp"

int main()
{
  TestResult result;

  lib::String arg1 = "file=toto.sitl";
  arg1.push_back('\0');
  lib::String arg2 = "verbose";
  arg2.push_back('\0');
  lib::String arg3 = "int=-1200";
  arg3.push_back('\0');
  lib::String arg4 = "uint=1200";
  arg4.push_back('\0');

  char *argv[] = {arg1.data(), arg2.data(),
                  arg3.data(), arg4.data()};
  int argc = 4;

  lib::CommandLine cmdl(argc, argv);

  test(cmdl.size() == 4, result);
  test(!cmdl.empty(), result);
  test(cmdl.contains("file"), result);
  test(cmdl.value("file") == sv("toto.sitl"), result);
  test(cmdl.value("verbose2") == sv(""), result);
  test(cmdl.flag("file"), result);
  test(cmdl.flag("verbose"), result);
  test(!cmdl.flag("verbose2"), result);
  test(cmdl.uinteger("uint") == 1200, result);
  test(cmdl.integer("uint") == 1200, result);
  test(cmdl.integer("int") == -1200, result);
  test(cmdl.uinteger("int") == 0, result);
  test(cmdl.uinteger("verbose") == 0, result);
  test(cmdl.integer("verbose") == 0, result);


  print_result(result);
}